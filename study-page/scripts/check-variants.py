"""Compile and execute concrete variants; instrument temporary copies for trace checks."""
from pathlib import Path
import concurrent.futures
import json
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
HEADERS = '''#include <algorithm>
#include <array>
#include <cassert>
#include <queue>
#include <random>
#include <stack>
#include <vector>
using namespace std;
using ll = long long;
'''
TESTS = {
    'sliding-fixed-sum': '''
nums = {2, 1, 3, 2}; K = 2; assert(maxWindowSum() == 5);
nums = {-3, -2}; K = 2; assert(maxWindowSum() == -5);
K = 1; assert(maxWindowSum() == -2);
nums = {}; K = 0; assert(maxWindowSum() == 0);
nums = {1}; K = 2; assert(maxWindowSum() == 0);
nums = {1000000000, 1000000000, 1000000000}; K = 3; assert(maxWindowSum() == 3000000000LL);
mt19937 rng(110); for (int test = 0; test < 250; test++) {
    int len = 1 + rng() % 25; nums.clear();
    for (int i = 0; i < len; i++) nums.push_back(int(rng() % 21) - 10);
    K = 1 + rng() % len; ll expected = -1000000000;
    for (int left = 0; left + K <= len; left++) {
        ll total = 0; for (int i = left; i < left + K; i++) total += nums[i];
        expected = max(expected, total);
    }
    assert(maxWindowSum() == expected);
}''',
    'sliding-min-sum': '''
nums = {2, 1, 3, 2}; target = 5; assert(minWindowLength() == 2);
nums = {}; target = 1; assert(minWindowLength() == 0);
nums = {1}; target = 1; assert(minWindowLength() == 1);
target = 2; assert(minWindowLength() == 0);
nums = {1000000000, 1000000000, 1000000000}; target = 3000000000LL; assert(minWindowLength() == 3);
mt19937 rng(111); for (int test = 0; test < 250; test++) {
    int len = rng() % 25; nums.clear();
    for (int i = 0; i < len; i++) nums.push_back(1 + rng() % 10);
    target = 1 + rng() % 100; int expected = len + 1;
    for (int left = 0; left < len; left++) {
        ll total = 0;
        for (int right = left; right < len; right++) {
            total += nums[right]; if (total >= target) expected = min(expected, right - left + 1);
        }
    }
    if (expected == len + 1) expected = 0;
    assert(minWindowLength() == expected);
}''',
    'binary-upper-bound': '''
nums = {1, 2, 2, 5}; assert(upperIndex(2) == 3); assert(upperIndex(5) == 4);
assert(upperIndex(-1) == 0); nums = {}; assert(upperIndex(0) == 0);
mt19937 rng(112); for (int test = 0; test < 250; test++) {
    nums.clear(); int len = rng() % 30;
    for (int i = 0; i < len; i++) nums.push_back(int(rng() % 15) - 7);
    sort(nums.begin(), nums.end());
    for (int x = -9; x <= 9; x++) { int expected = upper_bound(nums.begin(), nums.end(), x) - nums.begin(); assert(upperIndex(x) == expected); }
}''',
    'dfs-iterative': '''
edges = {{1, 2}, {0, 3}, {0}, {1}}; traverseIterative(0); assert((ans == vector<int>{0, 2, 1, 3}));
edges = {{}, {}}; traverseIterative(1); assert((visited == vector<int>{0, 1})); assert((ans == vector<int>{1}));
edges.assign(200000, {}); for (int i = 0; i < 199999; i++) edges[i].push_back(i + 1);
traverseIterative(0); assert(ans.size() == 200000 && ans.back() == 199999);
mt19937 rng(113); for (int test = 0; test < 100; test++) {
    int len = 1 + rng() % 15; edges.assign(len, {});
    for (int i = 0; i < len; i++) for (int j = 0; j < len; j++) if (rng() % 5 == 0) edges[i].push_back(j);
    int start = rng() % len; vector<int> expected(len, 0); queue<int> q; q.push(start); expected[start] = 1;
    while (!q.empty()) { int now = q.front(); q.pop(); for (int next : edges[now]) if (!expected[next]) { expected[next] = 1; q.push(next); } }
    traverseIterative(start); assert(visited == expected); vector<int> unique = ans; sort(unique.begin(), unique.end());
    assert(adjacent_find(unique.begin(), unique.end()) == unique.end());
}''',
    'floyd-reachability': '''
initReachability(3); addConnection(0, 1); addConnection(1, 2); transitiveClosure();
assert((reach == vector<vector<int>>{{1, 1, 1}, {0, 1, 1}, {0, 0, 1}}));
initReachability(1); transitiveClosure(); assert(reach[0][0] == 1);
initReachability(0); transitiveClosure(); assert(reach.empty());
mt19937 rng(114); for (int test = 0; test < 80; test++) {
    int len = 1 + rng() % 12; initReachability(len); vector<vector<int>> edges(len);
    for (int i = 0; i < len; i++) for (int j = 0; j < len; j++) if (rng() % 4 == 0) { addConnection(i, j); edges[i].push_back(j); }
    transitiveClosure();
    for (int start = 0; start < len; start++) {
        vector<int> expected(len, 0); queue<int> q; q.push(start); expected[start] = 1;
        while (!q.empty()) { int now = q.front(); q.pop(); for (int next : edges[now]) if (!expected[next]) { expected[next] = 1; q.push(next); } }
        assert(reach[start] == expected);
    }
}''',
    'dp-min-coins': '''
nums = {1, 3}; N = 4; assert(minCoins() == 2); assert((dp == vector<int>{0, 1, 2, 1, 2}));
nums = {}; N = 0; assert(minCoins() == 0); N = 1; assert(minCoins() == -1);
nums = {2, 4}; N = 7; assert(minCoins() == -1); nums = {1}; N = 100000; assert(minCoins() == 100000);
mt19937 rng(115); for (int test = 0; test < 200; test++) {
    N = rng() % 45; nums.clear(); int len = rng() % 8;
    for (int i = 0; i < len; i++) nums.push_back(1 + rng() % 10);
    vector<int> expected(N + 1, -1); expected[0] = 0; queue<int> q; q.push(0);
    while (!q.empty()) { int now = q.front(); q.pop(); for (int next : nums) if (now + next <= N && expected[now + next] == -1) { expected[now + next] = expected[now] + 1; q.push(now + next); } }
    assert(minCoins() == expected[N]);
}'''
}


def observe(name, code):
    if name == 'sliding-fixed-sum':
        hook = '        }\n    }\n    return ans;'
        code = code.replace(hook, '        }\n        record(right, sum, ans);\n    }\n    return ans;')
        prefix = 'vector<array<ll, 3>> seen; void record(int i, ll total, ll best) { seen.push_back({i, total, best}); }\n'
        test = 'nums = {2, 1, 3, 2}; K = 2; maxWindowSum(); assert((seen == vector<array<ll, 3>>{{0,2,0},{1,3,3},{2,4,4},{3,5,5}}));'
    elif name == 'sliding-min-sum':
        code = code.replace('        sum += nums[right];', '        sum += nums[right]; record(right, left, sum, ans);').replace('            left++;', '            left++; record(right, left, sum, ans);')
        prefix = 'vector<array<ll, 4>> seen; void record(int r, int l, ll total, int best) { seen.push_back({r,l,total,best}); }\n'
        test = 'nums = {2,1,3,2}; target = 5; minWindowLength(); assert((seen == vector<array<ll,4>>{{0,0,2,5},{1,0,3,5},{2,0,6,5},{2,1,4,3},{3,1,6,3},{3,2,5,3},{3,3,2,2}}));'
    elif name == 'binary-upper-bound':
        code = code.replace('        else right = mid;', '        else right = mid;\n        record(left, right, mid);')
        prefix = 'vector<array<int,3>> seen; void record(int l, int r, int m) { seen.push_back({l,r,m}); }\n'
        test = 'nums = {1,2,2,5}; assert(upperIndex(2) == 3); assert((seen == vector<array<int,3>>{{3,4,2},{3,3,3}}));'
    elif name == 'dfs-iterative':
        code = code.replace('        }\n    }\n}', '        }\n        record(st);\n    }\n}')
        prefix = 'vector<vector<int>> seen; void record(stack<int> st) { vector<int> row; while (!st.empty()) { row.push_back(st.top()); st.pop(); } reverse(row.begin(), row.end()); seen.push_back(row); }\n'
        test = 'edges = {{1,2},{0,3},{0},{1}}; traverseIterative(0); assert((seen == vector<vector<int>>{{1,2},{1},{3},{}}));'
    elif name == 'floyd-reachability':
        code = code.replace('        }\n    }\n}', '        }\n        record(k, reach[0][2]);\n    }\n}')
        prefix = 'vector<array<int,2>> seen; void record(int k, int value) { seen.push_back({k,value}); }\n'
        test = 'initReachability(3); addConnection(0,1); addConnection(1,2); transitiveClosure(); assert((seen == vector<array<int,2>>{{0,0},{1,1},{2,1}}));'
    else:
        code = code.replace('        }\n    }\n    if (dp[N]', '        }\n        record(now, dp[now]);\n    }\n    if (dp[N]')
        prefix = 'vector<array<int,2>> seen; void record(int now, int value) { seen.push_back({now,value}); }\n'
        test = 'nums = {1,3}; N = 4; minCoins(); assert((seen == vector<array<int,2>>{{1,1},{2,2},{3,1},{4,2}}));'
    assert 'record(' in code
    return HEADERS + prefix + code + '\nint main() { ' + test + ' }\n'


def run(item):
    name, body = item
    path = ROOT / 'templates/variants' / (name + '.cpp')
    code = path.read_text()
    with tempfile.TemporaryDirectory(prefix='study-variant-') as folder:
        folder = Path(folder)
        try:
            subprocess.run(['g++', '-std=c++17', '-Wall', '-Wextra', '-pedantic', '-fsyntax-only', str(path)], check=True, capture_output=True, text=True, timeout=60)
            for phase, source in [('runtime', HEADERS + code + '\nint main() {\n' + body + '\n}\n'), ('trace', observe(name, code))]:
                source_path = folder / (phase + '.cpp')
                executable = folder / phase
                source_path.write_text(source)
                subprocess.run(['g++', '-std=c++17', '-O2', '-fsanitize=undefined', '-fno-sanitize-recover=undefined', str(source_path), '-o', str(executable)], check=True, capture_output=True, text=True, timeout=60)
                subprocess.run([str(executable)], check=True, capture_output=True, text=True, timeout=20)
            return {'file': name, 'passed': True, 'standaloneHeaders': True, 'sampleTrace': True}
        except (subprocess.CalledProcessError, subprocess.TimeoutExpired) as error:
            return {'file': name, 'passed': False, 'details': str(error) + '\n' + (getattr(error, 'stderr', '') or '')[:3000]}


if __name__ == '__main__':
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        results = list(pool.map(run, TESTS.items()))
    for result in results:
        print(('PASS ' if result['passed'] else 'FAIL ') + result['file'], flush=True)
        if not result['passed']:
            print(result['details'], flush=True)
    (ROOT / 'docs/variant-results.json').write_text(json.dumps({'results': results}, ensure_ascii=False, indent=2) + '\n')
    raise SystemExit(0 if all(result['passed'] for result in results) else 1)
