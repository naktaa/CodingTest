"""Generate replay data by executing instrumented copies of the displayed C++.
Canonical templates are never edited. Requires Python 3 and g++ only to regenerate.
The website itself reads the committed JSON and needs only Node.js.
"""
from pathlib import Path
import argparse, subprocess, tempfile, json, hashlib, random
ROOT = Path(__file__).absolute().parents[1]
parser=argparse.ArgumentParser();parser.add_argument('--check',action='store_true');args=parser.parse_args()
FIXTURES={
 'sliding-window':[
  {'id':'abba','label':'중복이 두 번 제거되는 abba','input':{'s':'abba'},'expected':2},
  {'id':'empty','label':'빈 문자열','input':{'s':''},'expected':0},
  {'id':'same','label':'모두 같은 문자 aaaa','input':{'s':'aaaa'},'expected':1},
  {'id':'repeat','label':'반복되는 abcabcbb','input':{'s':'abcabcbb'},'expected':3}],
 'monotonic-deque':[
  {'id':'basic','label':'앞 만료와 뒤 제거: [4,2,3,1], K=2','input':{'nums':[4,2,3,1],'K':2},'expected':[4,3,3]},
  {'id':'same','label':'같은 값: [4,4,4], K=2','input':{'nums':[4,4,4],'K':2},'expected':[4,4]},
  {'id':'one','label':'윈도우 길이 1','input':{'nums':[2,1,3],'K':1},'expected':[2,1,3]},
  {'id':'invalid','label':'원소보다 큰 윈도우','input':{'nums':[2,1],'K':3},'expected':[]}],
 'binary-search':[
  {'id':'duplicates','label':'중복된 값: [1,2,2,5], x=2','input':{'nums':[1,2,2,5],'x':2},'expected':1},
  {'id':'end','label':'최댓값보다 큰 x=9 → end','input':{'nums':[1,2,2,5],'x':9},'expected':4},
  {'id':'begin','label':'최솟값보다 작은 x=0 → begin','input':{'nums':[1,2,2,5],'x':0},'expected':0},
  {'id':'empty','label':'빈 배열','input':{'nums':[],'x':2},'expected':0}]
}
PREFIX='''#include <iostream>
#include <iomanip>
#include <deque>
#include <string>
#include <vector>
using namespace std;
void traceStep(int line, const char* event, int left = -1, int right = -1, int mid = -1,
               const deque<int>* dq = nullptr, int current = -1);
'''
def instrument(topic, code):
    seen=set();out=[]
    def call(line,event,params='left, right'):
        return f'traceStep({line}, "{event}", {params});'
    for line,text in enumerate(code.splitlines(),1):
        s=text.strip();replacement=None;after=None;before=None
        if s in ['int len = s.size();', 'int len = nums.size();']:
            after=call(line,'length','-1, -1');seen.add(s)
        if topic=='sliding-window':
            actions={
             'fill(cnt, cnt + 128, 0);':('reset','-1, -1'),
             'int left = 0;':('left','left, -1'),
             'ans = 0;':('answer-init','left, -1'),
             'for (int right = 0; right < len; right++) {':('visit','left, right'),
             'char now = s[right];':('character','left, right, -1, nullptr, now'),
             'cnt[now]++;':('add','left, right'),
             'char next = s[left];':('remove-target','left, right, -1, nullptr, next'),
             'cnt[next]--;':('remove','left, right, -1, nullptr, next'),
             'left++;':('advance-left','left, right'),
             'ans = max(ans, right - left + 1);':('answer','left, right')}
            if s in actions:ev,params=actions[s];after=call(line,ev,params);seen.add(s)
            if s=='while (cnt[now] > 1) {':
                replacement=f'while ((traceStep({line}, "condition", left, right), cnt[now] > 1)) {{';seen.add(s)
            if s=='return ans;':before=call(line,'return','left, len');seen.add(s)
        elif topic=='monotonic-deque':
            params='i - K + 1, i, -1, &dq'
            actions={'ans.clear();':('reset','-1, -1'), 'deque<int> dq;':('deque-init','-1, -1, -1, &dq'),
             'for (int i = 0; i < len; i++) {':('visit',params),
             'dq.push_back(i);':('push',params)}
            if s in actions:ev,p=actions[s];after=call(line,ev,p);seen.add(s)
            if s=='if (K <= 0 || K > len) return;':
                before=call(line,'validity','-1, -1');seen.add(s)
            if s.startswith('while (!dq.empty() && dq.front()'):
                condition='!dq.empty() && dq.front() < i - K + 1'
                replacement=f'while ((traceStep({line}, "expire-check", {params}), {condition})) {{ dq.pop_front(); {call(line,"expire",params)} }}';seen.add(s)
            if s.startswith('while (!dq.empty() && nums[dq.back()]'):
                condition='!dq.empty() && nums[dq.back()] <= nums[i]'
                replacement=f'while ((traceStep({line}, "back-check", {params}), {condition})) {{ dq.pop_back(); {call(line,"drop-back",params)} }}';seen.add(s)
            if s=='if (i >= K - 1) ans.push_back(nums[dq.front()]);':
                replacement=f'traceStep({line}, "window-check", {params}); if (i >= K - 1) {{ ans.push_back(nums[dq.front()]); {call(line,"answer",params)} }}';seen.add(s)
            if line==len(code.splitlines()):before=call(line,'return','len - K, len - 1, -1, &dq');seen.add('end')
        else:
            if s=='int left = 0;':after=call(line,'left','left, -1');seen.add(s)
            if s=='int right = len;':after=call(line,'right');seen.add(s)
            if s=='while (left < right) {':replacement=f'while ((traceStep({line}, "condition", left, right), left < right)) {{';seen.add(s)
            if s=='int mid = left + (right - left) / 2;':after=call(line,'middle','left, right, mid');seen.add(s)
            if s=='if (nums[mid] < x) left = mid + 1;':replacement=f'traceStep({line}, "compare", left, right, mid); if (nums[mid] < x) {{ left = mid + 1; {call(line,"move-left","left, right, mid")} }}';seen.add(s)
            if s=='else right = mid;':replacement=f'else {{ right = mid; {call(line,"move-right","left, right, mid")} }}';seen.add(s)
            if s=='return left;':before=call(line,'return');seen.add(s)
        indent = text[:len(text) - len(text.lstrip())]
        if before: out.append(indent + before)
        out.append(indent + replacement if replacement else text)
        if after: out.append(indent + ('    ' if s.endswith('{') else '') + after)
    expected={'sliding-window':13,'monotonic-deque':10,'binary-search':8}[topic]
    assert len(seen)==expected,(topic,seen)
    return '\n'.join(out)+'\n'

def logger(topic):
    extra = ''
    if topic == 'sliding-window':
        extra = r'''
    cout << ",\"ans\":" << ans << ",\"cnt\":{";
    bool first = true;
    for (int c = 0; c < 128; c++) {
        char now = c;
        if (s.find(now) == string::npos) continue;
        if (!first) cout << ",";
        first = false;
        cout << quoted(string(1, now)) << ":" << cnt[c];
    }
    cout << "}";
'''
    elif topic == 'monotonic-deque':
        extra = r'''
    cout << ",\"ans\":[";
    int len = ans.size();
    for (int i = 0; i < len; i++) {
        if (i > 0) cout << ",";
        cout << ans[i];
    }
    cout << "],\"dq\":[";
    int size = 0;
    if (dq != nullptr) size = dq->size();
    for (int i = 0; i < size; i++) {
        if (i > 0) cout << ",";
        cout << (*dq)[i];
    }
    cout << "]";
'''
    return r'''
void traceStep(int line, const char* event, int left, int right, int mid,
               const deque<int>* dq, int current) {
    cout << "{\"line\":" << line << ",\"event\":\"" << event
         << "\",\"state\":{\"left\":" << left << ",\"right\":" << right
         << ",\"mid\":" << mid << ",\"current\":" << current;
''' + extra + r'''
    cout << "}}\n";
}
'''


def main_code(topic):
    if topic == 'sliding-window':
        return r'''
int main() {
    getline(cin, s);
    int result = longestUnique();
    cout << "{\"result\":" << result << "}\n";
}
'''
    setup = r'''
int main() {
    int N;
    cin >> N;
    nums.resize(N);
    for (int& now : nums) cin >> now;
'''
    if topic == 'binary-search':
        return setup + r'''
    int x;
    cin >> x;
    int result = lowerIndex(x);
    cout << "{\"result\":" << result << "}\n";
}
'''
    return setup + r'''
    cin >> K;
    windowMaximum();
    cout << "{\"result\":[";
    int len = ans.size();
    for (int i = 0; i < len; i++) {
        if (i > 0) cout << ",";
        cout << ans[i];
    }
    cout << "]}\n";
}
'''


def input_text(topic,data):
    if topic=='sliding-window':return data['s']+'\n'
    return str(len(data['nums']))+'\n'+' '.join(map(str,data['nums']))+'\n'+str(data['K' if topic=='monotonic-deque' else 'x'])+'\n'

def reference(topic,data):
    if topic=='sliding-window':
        s=data['s'];best=0
        for i in range(len(s)):
            seen=set()
            for j in range(i,len(s)):
                if s[j] in seen:break
                seen.add(s[j]);best=max(best,j-i+1)
        return best
    a=data['nums']
    if topic=='binary-search':return next((i for i,v in enumerate(a) if v>=data['x']),len(a))
    k=data['K'];return [max(a[i:i+k]) for i in range(len(a)-k+1)] if 0<k<=len(a) else []

def run(exe,topic,data):
    result=subprocess.run([str(exe)],input=input_text(topic,data),text=True,capture_output=True,check=True,timeout=5)
    return [json.loads(s) for s in result.stdout.splitlines()]

with tempfile.TemporaryDirectory(prefix='study-traces-') as temp:
    temp=Path(temp);total=0
    for topic,fixtures in FIXTURES.items():
        source=(ROOT/'templates'/f'{topic}.cpp').read_text();digest=hashlib.sha256(source.encode()).hexdigest()
        executables=[]
        for mode in ['plain','trace']:
            cpp=temp/f'{topic}-{mode}.cpp';exe=cpp.with_suffix('')
            cpp.write_text(PREFIX+(instrument(topic,source) if mode=='trace' else source)+(logger(topic) if mode=='trace' else '')+'\n'+main_code(topic))
            subprocess.run(['g++','-std=c++17','-O2',str(cpp),'-o',str(exe)],check=True,capture_output=True)
            executables.append(exe)
        cases=[]
        for f in fixtures:
            rows=run(executables[1],topic,f['input']);plain=run(executables[0],topic,f['input'])[-1]['result']
            assert plain==rows[-1]['result']==f['expected']==reference(topic,f['input'])
            previous=None;steps=[]
            for row in rows[:-1]:
                state=row['state'];steps.append({'line':row['line'],'event':row['event'],'before':previous,'after':state});previous=state
            cases.append({**f,'steps':steps})
        rng=random.Random(20261022)
        for _ in range(100):
            if topic=='sliding-window':data={'s':''.join(rng.choice('abcd') for _ in range(rng.randrange(16)))}
            else:
                a=[rng.randrange(-5,10) for _ in range(rng.randrange(12))]
                data={'nums':sorted(a),'x':rng.randrange(-7,12)} if topic=='binary-search' else {'nums':a,'K':rng.randrange(0,len(a)+3)}
            assert run(executables[0],topic,data)[-1]['result']==run(executables[1],topic,data)[-1]['result']==reference(topic,data)
            total+=1
        payload={'topic':topic,'sourceHash':digest,'generator':'C++17 execution of instrumented canonical template','sourceLines':len(source.splitlines()),'cases':cases}
        path=ROOT/'src/data/traces'/f'{topic}.json'
        if args.check:assert json.loads(path.read_text())==payload,f'Stale replay data: {topic}'
        else:path.write_text(json.dumps(payload,ensure_ascii=False,indent=2)+'\n')
        print(f'{topic}: {len(cases)} examples, {sum(len(x["steps"]) for x in cases)} C++ steps verified',flush=True)
    print(f'{total} differential cases passed (original C++ / traced C++ / brute reference).')
