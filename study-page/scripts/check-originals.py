"""Compile/run selected repository solutions without editing their source."""
from pathlib import Path
import subprocess, tempfile, concurrent.futures, json
root=Path(__file__).resolve().parents[2]
headers='#include <cassert>\n#include <iostream>\n#include <vector>\n#include <string>\n#include <algorithm>\n#include <queue>\n#include <functional>\n'
cases=[
('Baekjoon/최단거리/1753_최단경로.cpp',None,[('5 6\n1\n5 1 1\n1 2 2\n1 3 3\n2 3 4\n2 4 5\n3 4 6\n','0 2 3 7 INF'),('1 0\n1\n','0')]),
('Baekjoon/DP/12865_평범한+배낭.cpp',None,[('4 7\n6 13\n4 8\n3 6\n5 12\n','14'),('1 1\n2 5\n','0')]),
('Baekjoon/DP/11066_파일+합치기.cpp',None,[('1\n4\n40 30 30 50\n','300'),('1\n2\n1 2\n','3')]),
('Baekjoon/그래프/2178_미로+탐색.cpp',None,[('4 6\n101111\n101010\n101011\n111011\n','15')]),
('LeetCode/단조스택+큐/239_Sliding Window Maximum.cpp','Solution sol;vector<int>a={1,3,-1,-3,5,3,6,7};assert((sol.maxSlidingWindow(a,3)==vector<int>{3,3,5,5,6,7}));a={2,2};assert((sol.maxSlidingWindow(a,1)==a));',[]),
('LeetCode/단조스택+큐/739_Daily Temperatures.cpp','Solution sol;vector<int>a={73,74,75,71,69,72,76,73};assert((sol.dailyTemperatures(a)==vector<int>{1,1,4,2,1,1,0,0}));a={2,2};assert((sol.dailyTemperatures(a)==vector<int>{0,0}));',[]),
('LeetCode/누적합/1094_Car Pooling.cpp','Solution sol;vector<vector<int>>a={{2,1,5},{3,3,7}};assert(!sol.carPooling(a,4));assert(sol.carPooling(a,5));a={{2,1,5},{3,5,7}};assert(sol.carPooling(a,3));',[]),
('LeetCode/슬라이딩윈도우/3_Longest Substring Without Repeating Characters.cpp','Solution sol;assert(sol.lengthOfLongestSubstring("abba")==2);assert(sol.lengthOfLongestSubstring("")==0);assert(sol.lengthOfLongestSubstring("abcabcbb")==3);',[]),
('LeetCode/정렬/56_Merge Intervals.cpp','Solution sol;vector<vector<int>>a={{1,3},{2,6},{8,10},{15,18}};assert((sol.merge(a)==vector<vector<int>>{{1,6},{8,10},{15,18}}));a={{1,10},{2,3}};assert((sol.merge(a)==vector<vector<int>>{{1,10}}));',[]),
('Programmers/힙/더맵게.cpp','assert(solution({1,2,3,9,10,12},7)==2);assert(solution({1},7)==-1);assert(solution({7},7)==0);',[])
]
def run(case):
 name,body,examples=case
 with tempfile.TemporaryDirectory(prefix='codingtest-original-') as tmp:
  source=Path(tmp)/'source.cpp';exe=Path(tmp)/'program'
  original=(root/name).read_bytes().decode('utf8')
  source.write_text((headers+original+'\nint main(){'+body+'}\n') if body else original)
  compiled=subprocess.run(['g++','-std=c++17','-O2',str(source),'-o',str(exe)],capture_output=True,text=True,timeout=90)
  if compiled.returncode:return {'path':name,'passed':False,'phase':'compile','details':compiled.stderr[:1000]}
  inputs=examples if not body else [('', '')]
  for inp,expected in inputs:
   result=subprocess.run([str(exe)],input=inp,capture_output=True,text=True,timeout=5)
   if result.returncode or (not body and result.stdout.split()!=expected.split()):
    return {'path':name,'passed':False,'phase':'run','expected':expected,'actual':result.stdout,'details':result.stderr[:1000]}
  return {'path':name,'passed':True,'runs':len(inputs)}
with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:results=list(pool.map(run,cases))
for r in results:print(('PASS ' if r['passed'] else 'FAIL ')+r['path']+((' '+str(r)) if not r['passed'] else ''),flush=True)
(root/'study-page/docs/original-results.json').write_text(json.dumps(results,ensure_ascii=False,indent=2)+'\n')
raise SystemExit(0 if all(r['passed'] for r in results) else 1)
