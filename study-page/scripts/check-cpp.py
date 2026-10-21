"""Run with Python 3 + g++ (C++17). All executables are temporary."""
from pathlib import Path
import concurrent.futures, subprocess, tempfile, json, time, sys
root=Path(__file__).resolve().parents[1]
tests={
'complexity':'n=4; assert(countPairs()==6); n=0; assert(countPairs()==0); n=1; assert(countPairs()==0);',
'implementation':'s="aaabbc";assert(countGroups()==3);s="";assert(countGroups()==0);s="aaa";assert(countGroups()==1);',
'sorting':'arr={{80,"B"},{90,"C"},{90,"A"}};sortRecords();assert(arr[0].second=="A"&&arr[1].second=="C");assert(!cmp(arr[0],arr[0]));arr.clear();sortRecords();',
'frequency':'arr={2,2,5};countValues();removeValue(2);assert(cnt[2]==1);removeValue(2);assert(cnt.size()==1);removeValue(9);assert(cnt.size()==1);arr={};countValues();assert(cnt.empty());',
'stack-queue':'s="(())";assert(validParentheses());s="((";assert(!validParentheses());s=")(";assert(!validParentheses());s="";assert(validParentheses());',
'heap':'arr={4,1,3};extractSorted();assert((ans==vector<int>{1,3,4}));arr={};extractSorted();assert(ans.empty());',
'prefix':'arr={2,1,4};buildPrefix();assert(rangeSum(1,3)==5);assert(rangeSum(0,0)==0);arr={-2};buildPrefix();assert(rangeSum(0,1)==-2);',
'difference':'initDifference(4);addRange(1,3,2);restore();assert((ans==vector<long long>{0,2,2,0}));initDifference(1);addRange(0,1,7);addRange(0,1,-2);restore();assert(ans[0]==5);',
'two-pointers':'arr={1,2,4,7};target=6;assert(hasPair());arr={3};target=6;assert(!hasPair());arr={};assert(!hasPair());arr={-3,-2,4};target=1;assert(hasPair());',
'sliding-window':'''s="abba";assert(longestUnique()==2);s="";assert(longestUnique()==0);mt19937 rng(91);for(int t=0;t<250;t++){s="";int len=rng()%20;for(int i=0;i<len;i++)s+=char('a'+rng()%5);int expected=0;for(int i=0;i<len;i++){bool seen[256]={};for(int j=i;j<len;j++){unsigned char c=s[j];if(seen[c])break;seen[c]=true;expected=max(expected,j-i+1);}}assert(longestUnique()==expected);}''',
'binary-search':'arr={1,2,2,5};assert(lowerIndex(2)==1);assert(lowerIndex(6)==4);assert(lowerIndex(-1)==0);arr.clear();assert(lowerIndex(3)==0);',
'compression':'arr={100,-5,100,7};compress();assert((compressed==vector<int>{2,0,2,1}));assert(coords.size()==3);arr={};compress();assert(compressed.empty());',
'greedy':'intervals={{1,4},{2,3},{3,5}};assert(maxMeetings()==2);intervals={};assert(maxMeetings()==0);intervals={{-4,-2},{-2,1}};assert(maxMeetings()==2);',
'intervals':'intervals={{1,3},{2,5},{8,9}};mergeIntervals();assert((ans==vector<pair<int,int>>{{1,5},{8,9}}));intervals={{1,10},{2,3}};mergeIntervals();assert(ans[0].second==10);intervals.clear();mergeIntervals();assert(ans.empty());',
'bruteforce':'arr={1,2};target=3;assert(countSubsets()==1);arr={-1,1};target=0;assert(countSubsets()==2);arr={};assert(countSubsets()==1);',
'backtracking':'n=3;m=2;combinations();assert((ans==vector<vector<int>>{{0,1},{0,2},{1,2}}));m=0;combinations();assert(ans.size()==1&&ans[0].empty());m=4;combinations();assert(ans.empty());',
'permutations':'arr={1,1,2};permutations();assert(ans.size()==3);assert((ans.front()==vector<int>{1,1,2}));arr={};permutations();assert(ans.size()==1);',
'math':'assert(gcdValue(48,18)==6);assert(gcdValue(0,4)==4);assert(gcdValue(0,0)==0);assert(gcdValue(1,999999999)==1);',
'bits':'initMask();addValue(0);addValue(2);assert(mask==5);removeValue(0);assert(mask==4);removeValue(0);assert(mask==4);addValue(63);assert(contains(63));initMask();assert(mask==0);',
'dfs':'edges={{1,2},{0,3},{0},{1}};runDfs(0);assert((visited==vector<int>{1,1,1,1}));edges={{},{}};runDfs(1);assert((visited==vector<int>{0,1}));',
'bfs':'edges={{1,2},{3},{3},{}};bfs(0);assert((dist==vector<int>{0,1,1,2}));edges={{},{}};bfs(1);assert((dist==vector<int>{-1,0}));',
'multi-bfs':'edges={{1},{0,2},{1,3},{2,4},{3}};starts={0,4,4};multiBfs();assert((dist==vector<int>{0,1,2,1,0}));starts={};multiBfs();for(int d:dist)assert(d==-1);',
'state-bfs':'grid={{0,1},{0,0}};stateBfs();assert(dist[1][1][0]==2&&dist[1][1][1]==2);grid={{0}};stateBfs();assert(dist[0][0][0]==0);grid={{0,1,1}};stateBfs();assert(dist[0][2][0]==-1&&dist[0][2][1]==-1);',
'heap-simulation':'jobs={{0,3},{1,9},{2,6}};scheduleJobs();assert((ans==vector<int>{0,2,1}));jobs={{9,1},{0,2},{9,1}};scheduleJobs();assert((ans==vector<int>{1,0,2}));jobs={};scheduleJobs();assert(ans.empty());',
'monotonic-stack':'arr={2,1,3};nextGreaterDistance();assert((ans==vector<int>{2,1,0}));arr={2,2,2};nextGreaterDistance();assert((ans==vector<int>{0,0,0}));arr={};nextGreaterDistance();assert(ans.empty());',
'monotonic-deque':'''mt19937 rng(11);for(int t=0;t<300;t++){int len=1+rng()%30;arr.clear();for(int i=0;i<len;i++)arr.push_back(int(rng()%20)-10);k=1+rng()%len;vector<int> expected;for(int i=0;i+k<=len;i++)expected.push_back(*max_element(arr.begin()+i,arr.begin()+i+k));windowMaximum();assert(ans==expected);}k=0;windowMaximum();assert(ans.empty());''',
'parametric':'lengths={7,10};need=5;assert(maxLength()==3);lengths={1};need=2;assert(maxLength()==0);need=1;assert(maxLength()==1);lengths.clear();assert(maxLength()==0);',
'dijkstra':'''mt19937 rng(31);for(int t=0;t<80;t++){int n=1+rng()%8;edges.assign(n,{});vector<vector<long long>> ref(n,vector<long long>(n,INF));for(int i=0;i<n;i++){ref[i][i]=0;for(int j=0;j<n;j++)if(i!=j&&rng()%3==0){int w=rng()%15;edges[i].push_back({j,w});ref[i][j]=w;}}for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(ref[i][k]!=INF&&ref[k][j]!=INF)ref[i][j]=min(ref[i][j],ref[i][k]+ref[k][j]);for(int i=0;i<n;i++){dijkstra(i);assert(dist==ref[i]);}}''',
'floyd':'initFloyd(3);addEdge(0,1,8);addEdge(0,1,3);addEdge(1,2,4);addEdge(0,2,10);floyd();assert(dist[0][2]==7);assert(dist[2][0]==INF);initFloyd(1);floyd();assert(dist[0][0]==0);',
'topological':'edges={{2},{2},{}};assert(topologicalSort());assert((ans==vector<int>{0,1,2}));edges={{1},{0}};assert(!topologicalSort());edges={{}};assert(topologicalSort()&&ans.size()==1);',
'dsu':'initDsu(4);assert(unite(0,1));assert(unite(1,2));assert(find(0)==find(2));assert(!unite(2,0));assert(componentSize[find(0)]==3);initDsu(2);assert(find(0)!=find(1));',
'mst':'n=3;edges={{1,0,1},{2,1,2},{5,0,2}};assert(kruskal()&&ans==3);n=3;edges={{1,0,1}};assert(!kruskal());n=1;edges={};assert(kruskal()&&ans==0);',
'dp':'n=4;assert(countWays()==5);n=0;assert(countWays()==1);n=1;assert(countWays()==1);n=90;assert(countWays()==4660046610375530309LL);',
'knapsack':'''mt19937 rng(22);for(int t=0;t<120;t++){items.clear();int len=rng()%10;capacity=rng()%20;for(int i=0;i<len;i++)items.push_back({1+int(rng()%8),int(rng()%20)});long long expected=0;for(int mask=0;mask<(1<<len);mask++){int w=0,v=0;for(int i=0;i<len;i++)if(mask&(1<<i)){w+=items[i].first;v+=items[i].second;}if(w<=capacity)expected=max(expected,1LL*v);}assert(knapsack()==expected);}''',
'lis':'''mt19937 rng(33);for(int t=0;t<120;t++){arr.clear();int len=rng()%11;for(int i=0;i<len;i++)arr.push_back(int(rng()%8)-4);int expected=0;for(int mask=0;mask<(1<<len);mask++){bool ok=true;int last=-100,count=0;for(int i=0;i<len;i++)if(mask&(1<<i)){if(arr[i]<=last)ok=false;last=arr[i];count++;}if(ok)expected=max(expected,count);}assert(lisLength()==expected);}''',
'interval-dp':'arr={10,20,30};assert(mergeCost()==90);arr={7};assert(mergeCost()==0);arr={};assert(mergeCost()==0);arr={0,0,0};assert(mergeCost()==0);',
'tree':'edges={{1,2},{0,3},{0},{1}};traverse(0);assert((depth==vector<int>{0,1,1,2}));assert((order==vector<int>{0,1,3,2}));edges={{}};traverse(0);assert(parent[0]==0&&depth[0]==0);',
'tree-dp':'edges={{1,2},{0},{0}};weight={5,4,4};assert(independentSet(0)==8);weight={-1,-2,-3};assert(independentSet(0)==0);edges={{}};weight={7};assert(independentSet(0)==7);',
'zero-one-bfs':'edges={{{1,1},{2,0}},{},{{1,0}}};zeroOneBfs(0);assert((dist==vector<int>{0,0,0}));edges={{},{}};zeroOneBfs(1);assert(dist[1]==0&&dist[0]>100);',
'bellman-ford':'n=3;edges={{1,2,-2},{0,1,4},{0,2,5}};assert(bellmanFord(0));assert(dist[2]==2);edges={{0,1,1},{1,2,-2},{2,1,-1}};assert(!bellmanFord(0));n=3;edges={{1,2,-1},{2,1,-1}};assert(bellmanFord(0)&&dist[1]==INF);',
'bitmask-dp':'''mt19937 rng(55);for(int t=0;t<70;t++){int n=1+rng()%6;cost.assign(n,vector<int>(n));for(auto& row:cost)for(auto& v:row)v=int(rng()%20)-5;vector<int> perm(n);iota(perm.begin(),perm.end(),0);long long expected=100000;do{long long sum=0;for(int i=0;i<n;i++)sum+=cost[i][perm[i]];expected=min(expected,sum);}while(next_permutation(perm.begin(),perm.end()));assert(minAssignment()==expected);}cost={};assert(minAssignment()==0);''',
'fenwick':'''mt19937 rng(66);for(int len=1;len<=25;len++){initFenwick(len);vector<long long> ref(len,0);for(int t=0;t<100;t++){int idx=rng()%len;long long delta=int(rng()%20)-10;ref[idx]+=delta;add(idx+1,delta);int l=rng()%len,r=rng()%len;if(l>r)swap(l,r);long long sum=0;for(int i=l;i<=r;i++)sum+=ref[i];assert(rangeSum(l+1,r+1)==sum);}}''',
'segment-tree':'''mt19937 rng(77);for(int len=1;len<=25;len++){arr.assign(len,0);initSegment();vector<long long> ref(len,0);for(int t=0;t<100;t++){int idx=rng()%len;long long v=int(rng()%100)-50;ref[idx]=v;update(1,0,len-1,idx,v);int l=rng()%len,r=rng()%len;if(l>r)swap(l,r);long long sum=0;for(int i=l;i<=r;i++)sum+=ref[i];assert(query(1,0,len-1,l,r)==sum);}}arr={};initSegment();''',
'euler-tour':'edges={{1,2},{0,3},{0},{1}};eulerTour(0);assert((order==vector<int>{0,1,3,2}));assert(tin[1]==1&&tout[1]==3);assert(tout[0]-tin[0]==4);edges={{}};eulerTour(0);assert(tin[0]==0&&tout[0]==1);',
'lca':'''mt19937 rng(88);for(int len=1;len<=45;len++){edges.assign(len,{});for(int v=1;v<len;v++){int p=rng()%v;edges[p].push_back(v);edges[v].push_back(p);}for(int root: {0,len-1}){buildLca(root);for(int a=0;a<len;a++)for(int b=0;b<len;b++){int x=a,y=b;while(depth[x]>depth[y])x=parent[0][x];while(depth[y]>depth[x])y=parent[0][y];while(x!=y){x=parent[0][x];y=parent[0][y];}assert(lca(a,b)==x);}}}'''
}
# The test harness adds only reference-test dependencies; production snippets remain minimal.
headers='#include <cassert>\n#include <iostream>\n#include <random>\n#include <algorithm>\n#include <numeric>\n'
def run(item):
 id,body=item
 with tempfile.TemporaryDirectory(prefix='codingtest-cpp-') as tmp:
  source=Path(tmp)/'test.cpp';exe=Path(tmp)/'test'
  source.write_text(headers+(root/'templates'/f'{id}.cpp').read_text()+'\nint main(){\n'+body+'\n}\n')
  result=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra','-pedantic',str(source),'-o',str(exe)],capture_output=True,text=True,timeout=90)
  if result.returncode:return {'id':id,'passed':False,'phase':'compile','details':result.stderr[:3500]}
  check=subprocess.run([str(exe)],capture_output=True,text=True,timeout=15)
  return {'id':id,'passed':check.returncode==0,'phase':'run','details':check.stderr[:1000]}
selected={k:v for k,v in tests.items() if not sys.argv[1:] or k in sys.argv[1:]}
start=time.time()
with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:
 results=list(pool.map(run,selected.items()))
for r in results:
 print(('PASS ' if r['passed'] else 'FAIL ')+r['id']+(('\n'+r['details']) if not r['passed'] else ''),flush=True)
if sys.argv[1:] and (root/'docs/cpp-results.json').exists():
 previous=json.loads((root/'docs/cpp-results.json').read_text())['results']
 updates={r['id']:r for r in results}
 results=[updates.get(r['id'],r) for r in previous]
report={'compiler':'g++ -std=c++17 -O2 -Wall -Wextra -pedantic','elapsedSeconds':round(time.time()-start,2),'results':results}
(root/'docs/cpp-results.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
print('Passed',sum(r['passed'] for r in results),'/',len(results))
raise SystemExit(0 if all(r['passed'] for r in results) else 1)
