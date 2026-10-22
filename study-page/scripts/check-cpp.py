"""Run with Python 3 + g++ (C++17). All executables are temporary."""
from pathlib import Path
import concurrent.futures, subprocess, tempfile, json, time, sys
root=Path(__file__).resolve().parents[1]
tests={
'complexity':'N=4; assert(countPairs()==6); N=0; assert(countPairs()==0); N=1; assert(countPairs()==0);\nassert(1LL*200000*199999/2==19999900000LL);',
'implementation':'s="aaabbc";assert(countGroups()==3);s="";assert(countGroups()==0);s="aaa";assert(countGroups()==1);',
'sorting':'nums={{80,"B"},{90,"C"},{90,"A"}};sortRecords();assert(nums[0].second=="A"&&nums[1].second=="C");assert(!cmp(nums[0],nums[0]));nums.clear();sortRecords();',
'frequency':'nums={2,2,5};countValues();removeValue(2);assert(cnt[2]==1);removeValue(2);assert(cnt.size()==1);removeValue(9);assert(cnt.size()==1);nums={};countValues();assert(cnt.empty());',
'stack-queue':'s="(())";assert(validParentheses());s="((";assert(!validParentheses());s=")(";assert(!validParentheses());s="";assert(validParentheses());',
'heap':'nums={4,1,3};extractSorted();assert((ans==vector<int>{1,3,4}));nums={};extractSorted();assert(ans.empty());',
'prefix':'nums={2,1,4};buildPrefix();assert(rangeSum(1,3)==5);assert(rangeSum(0,0)==0);nums={-2};buildPrefix();assert(rangeSum(0,1)==-2);\nnums={1000000000,1000000000,1000000000};buildPrefix();assert(rangeSum(0,3)==3000000000LL);',
'difference':'initDifference(4);addRange(1,3,2);restore();assert((ans==vector<ll>{0,2,2,0}));initDifference(1);addRange(0,1,7);addRange(0,1,-2);restore();assert(ans[0]==5);\ninitDifference(1);for(int i=0;i<3;i++)addRange(0,1,1000000000);restore();assert(ans[0]==3000000000LL);',
'two-pointers':'nums={1,2,4,7};target=6;assert(hasPair());nums={3};target=6;assert(!hasPair());nums={};assert(!hasPair());nums={-3,-2,4};target=1;assert(hasPair());nums={1500000000,1500000000};target=3000000000LL;assert(hasPair());nums={-2000000000,-2000000000};target=-4000000000LL;assert(hasPair());',
'sliding-window':'s="abba";assert(longestUnique()==2);s="";assert(longestUnique()==0);mt19937 rng(91);for(int t=0;t<250;t++){s="";int len=rng()%20;for(int i=0;i<len;i++)s+=char(\'a\'+rng()%5);int expected=0;for(int i=0;i<len;i++){bool seen[256]={};for(int j=i;j<len;j++){unsigned char c=s[j];if(seen[c])break;seen[c]=true;expected=max(expected,j-i+1);}}assert(longestUnique()==expected);}\ns="Az! Az!";assert(longestUnique()==4);s=string(1,char(0))+string(1,char(127))+string(1,char(0));assert(longestUnique()==2);s=string(200000,\'a\');assert(longestUnique()==1);',
'binary-search':'nums={1,2,2,5};assert(lowerIndex(2)==1);assert(lowerIndex(6)==4);assert(lowerIndex(-1)==0);nums.clear();assert(lowerIndex(3)==0);',
'compression':'nums={100,-5,100,7};compress();assert((compressed==vector<int>{2,0,2,1}));assert(coords.size()==3);nums={};compress();assert(compressed.empty());\nnums={-1000000000,1000000000,-1000000000};compress();assert((compressed==vector<int>{0,1,0}));',
'greedy':'intervals={{1,4},{2,3},{3,5}};assert(maxMeetings()==2);intervals={};assert(maxMeetings()==0);intervals={{-4,-2},{-2,1}};assert(maxMeetings()==2);\nintervals={{-1000000000,-999999999},{999999999,1000000000}};assert(maxMeetings()==2);',
'intervals':'intervals={{1,3},{2,5},{8,9}};mergeIntervals();assert((ans==vector<pair<int,int>>{{1,5},{8,9}}));intervals={{1,10},{2,3}};mergeIntervals();assert(ans[0].second==10);intervals.clear();mergeIntervals();assert(ans.empty());',
'bruteforce':'nums={1,2};target=3;assert(countSubsets()==1);nums={-1,1};target=0;assert(countSubsets()==2);nums={};assert(countSubsets()==1);\nnums={1000000000,1000000000,1000000000};target=3000000000LL;assert(countSubsets()==1);nums.assign(20,0);target=0;assert(countSubsets()==1048576);',
'backtracking':'N=3;M=2;combinations();assert((ans==vector<vector<int>>{{0,1},{0,2},{1,2}}));M=0;combinations();assert(ans.size()==1&&ans[0].empty());M=4;combinations();assert(ans.empty());',
'permutations':'nums={1,1,2};permutations();assert(ans.size()==3);assert((ans.front()==vector<int>{1,1,2}));nums={};permutations();assert(ans.size()==1);',
'math':'assert(gcdValue(48,18)==6);assert(gcdValue(0,4)==4);assert(gcdValue(0,0)==0);assert(gcdValue(1,999999999)==1);',
'bits':'initMask();addValue(0);addValue(2);assert(mask==5);removeValue(0);assert(mask==4);removeValue(0);assert(mask==4);addValue(19);assert(contains(19));initMask();for(int i=0;i<20;i++)addValue(i);assert(mask==(1<<20)-1);for(int i=0;i<20;i++)assert(contains(i));removeValue(19);assert(!contains(19));initMask();assert(mask==0);',
'dfs':'edges={{1,2},{0,3},{0},{1}};runDfs(0);assert((visited==vector<int>{1,1,1,1}));edges={{},{}};runDfs(1);assert((visited==vector<int>{0,1}));',
'bfs':'edges={{1,2},{3},{3},{}};bfs(0);assert((dist==vector<int>{0,1,1,2}));edges={{},{}};bfs(1);assert((dist==vector<int>{-1,0}));',
'multi-bfs':'edges={{1},{0,2},{1,3},{2,4},{3}};starts={0,4,4};multiBfs();assert((dist==vector<int>{0,1,2,1,0}));starts={};multiBfs();for(int d:dist)assert(d==-1);',
'state-bfs':'grid={{0,1},{0,0}};stateBfs();assert(dist[1][1][0]==2&&dist[1][1][1]==2);grid={{0}};stateBfs();assert(dist[0][0][0]==0);grid={{0,1,1}};stateBfs();assert(dist[0][2][0]==-1&&dist[0][2][1]==-1);',
'heap-simulation':'jobs={{0,3},{1,9},{2,6}};scheduleJobs();assert((ans==vector<int>{0,2,1}));jobs={{9,1},{0,2},{9,1}};scheduleJobs();assert((ans==vector<int>{1,0,2}));jobs={};scheduleJobs();assert(ans.empty());\njobs={{0,1000000000},{0,1000000000},{0,1000000000},{0,1000000000},{1000000000,1}};scheduleJobs();assert((ans==vector<int>{0,4,1,2,3}));',
'monotonic-stack':'nums={2,1,3};nextGreaterDistance();assert((ans==vector<int>{2,1,0}));nums={2,2,2};nextGreaterDistance();assert((ans==vector<int>{0,0,0}));nums={};nextGreaterDistance();assert(ans.empty());',
'monotonic-deque':'mt19937 rng(11);for(int t=0;t<300;t++){int len=1+rng()%30;nums.clear();for(int i=0;i<len;i++)nums.push_back(int(rng()%20)-10);K=1+rng()%len;vector<int> expected;for(int i=0;i+K<=len;i++)expected.push_back(*max_element(nums.begin()+i,nums.begin()+i+K));windowMaximum();assert(ans==expected);}K=0;windowMaximum();assert(ans.empty());',
'parametric':'lengths={7,10};need=5;assert(maxLength()==3);lengths={1};need=2;assert(maxLength()==0);need=1;assert(maxLength()==1);lengths.clear();assert(maxLength()==0);\nlengths={1000000000,1000000000,1000000000};need=1000000000;assert(can(1));assert(!can(4));assert(maxLength()==2);',
'dijkstra':'mt19937 rng(31);for(int t=0;t<80;t++){int N=1+rng()%8;edges.assign(N,{});vector<vector<ll>> ref(N,vector<ll>(N,INF));for(int i=0;i<N;i++){ref[i][i]=0;for(int j=0;j<N;j++)if(i!=j&&rng()%3==0){int w=rng()%15;edges[i].push_back({j,w});ref[i][j]=w;}}for(int k=0;k<N;k++)for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(ref[i][k]!=INF&&ref[k][j]!=INF)ref[i][j]=min(ref[i][j],ref[i][k]+ref[k][j]);for(int i=0;i<N;i++){dijkstra(i);assert(dist==ref[i]);}}\nedges={{{1,1000000000}},{{2,1000000000}},{{3,1000000000}},{}};dijkstra(0);assert(dist[3]==3000000000LL);assert(INF>dist[3]);',
'floyd':'initFloyd(3);addEdge(0,1,8);addEdge(0,1,3);addEdge(1,2,4);addEdge(0,2,10);floyd();assert(dist[0][2]==7);assert(dist[2][0]==INF);initFloyd(1);floyd();assert(dist[0][0]==0);\ninitFloyd(4);addEdge(0,1,1000000000);addEdge(1,2,1000000000);addEdge(2,3,1000000000);floyd();assert(dist[0][3]==3000000000LL);initFloyd(3);addEdge(0,1,-1000000000);addEdge(1,2,-1000000000);floyd();assert(dist[0][2]==-2000000000LL);',
'topological':'edges={{2},{2},{}};assert(topologicalSort());assert((ans==vector<int>{0,1,2}));edges={{1},{0}};assert(!topologicalSort());edges={{}};assert(topologicalSort()&&ans.size()==1);',
'dsu':'initDsu(4);assert(unite(0,1));assert(unite(1,2));assert(find(0)==find(2));assert(!unite(2,0));assert(componentSize[find(0)]==3);initDsu(2);assert(find(0)!=find(1));',
'mst':'N=3;edges={{1,0,1},{2,1,2},{5,0,2}};assert(kruskal()&&ans==3);N=3;edges={{1,0,1}};assert(!kruskal());N=1;edges={};assert(kruskal()&&ans==0);\nN=4;edges={{1000000000,0,1},{1000000000,1,2},{1000000000,2,3}};assert(kruskal()&&ans==3000000000LL);',
'dp':'N=4;assert(countWays()==5);N=0;assert(countWays()==1);N=1;assert(countWays()==1);N=90;assert(countWays()==4660046610375530309LL);',
'knapsack':'mt19937 rng(22);for(int t=0;t<120;t++){items.clear();int len=rng()%10;capacity=rng()%20;for(int i=0;i<len;i++)items.push_back({1+int(rng()%8),int(rng()%20)});ll expected=0;for(int mask=0;mask<(1<<len);mask++){int w=0,v=0;for(int i=0;i<len;i++)if(mask&(1<<i)){w+=items[i].first;v+=items[i].second;}if(w<=capacity)expected=max(expected,1LL*v);}assert(knapsack()==expected);}\ncapacity=3;items={{1,1000000000},{1,1000000000},{1,1000000000}};assert(knapsack()==3000000000LL);',
'lis':'mt19937 rng(33);for(int t=0;t<120;t++){nums.clear();int len=rng()%11;for(int i=0;i<len;i++)nums.push_back(int(rng()%8)-4);int expected=0;for(int mask=0;mask<(1<<len);mask++){bool ok=true;int last=-100,count=0;for(int i=0;i<len;i++)if(mask&(1<<i)){if(nums[i]<=last)ok=false;last=nums[i];count++;}if(ok)expected=max(expected,count);}assert(lisLength()==expected);}',
'interval-dp':'nums={10,20,30};assert(mergeCost()==90);nums={7};assert(mergeCost()==0);nums={};assert(mergeCost()==0);nums={0,0,0};assert(mergeCost()==0);\nnums={1000000000,1000000000,1000000000};assert(mergeCost()==5000000000LL);',
'tree':'edges={{1,2},{0,3},{0},{1}};traverse(0);assert((depth==vector<int>{0,1,1,2}));assert((order==vector<int>{0,1,3,2}));edges={{}};traverse(0);assert(parent[0]==0&&depth[0]==0);',
'tree-dp':'edges={{1,2},{0},{0}};weight={5,4,4};assert(independentSet(0)==8);weight={-1,-2,-3};assert(independentSet(0)==0);edges={{}};weight={7};assert(independentSet(0)==7);edges={{1,2,3},{0},{0},{0}};weight={0,1000000000,1000000000,1000000000};assert(independentSet(0)==3000000000LL);',
'zero-one-bfs':'edges={{{1,1},{2,0}},{},{{1,0}}};zeroOneBfs(0);assert((dist==vector<int>{0,0,0}));edges={{},{}};zeroOneBfs(1);assert(dist[1]==0&&dist[0]>100);\nedges.assign(200000,{});for(int i=0;i<199999;i++)edges[i].push_back({i+1,1});zeroOneBfs(0);assert(dist.back()==199999);',
'bellman-ford':'N=3;edges={{1,2,-2},{0,1,4},{0,2,5}};assert(bellmanFord(0));assert(dist[2]==2);edges={{0,1,1},{1,2,-2},{2,1,-1}};assert(!bellmanFord(0));N=3;edges={{1,2,-1},{2,1,-1}};assert(bellmanFord(0)&&dist[1]==INF);\nN=4;edges={{0,1,1000000000},{1,2,1000000000},{2,3,1000000000}};assert(bellmanFord(0)&&dist[3]==3000000000LL);N=500;edges.assign(5000,edge{0,0,-1000000000});assert(!bellmanFord(0));',
'bitmask-dp':'mt19937 rng(55);for(int t=0;t<70;t++){int N=1+rng()%6;cost.assign(N,vector<int>(N));for(auto& row:cost)for(auto& v:row)v=int(rng()%20)-5;vector<int> perm(N);iota(perm.begin(),perm.end(),0);ll expected=100000;do{ll sum=0;for(int i=0;i<N;i++)sum+=cost[i][perm[i]];expected=min(expected,sum);}while(next_permutation(perm.begin(),perm.end()));assert(minAssignment()==expected);}cost={};assert(minAssignment()==0);\ncost.assign(4,vector<int>(4,1000000000));assert(minAssignment()==4000000000LL);assert(countBits((1<<20)-1)==20);',
'fenwick':'mt19937 rng(66);for(int len=1;len<=25;len++){initFenwick(len);vector<ll> ref(len,0);for(int t=0;t<100;t++){int idx=rng()%len;ll delta=int(rng()%20)-10;ref[idx]+=delta;add(idx+1,delta);int l=rng()%len,r=rng()%len;if(l>r)swap(l,r);ll sum=0;for(int i=l;i<=r;i++)sum+=ref[i];assert(rangeSum(l+1,r+1)==sum);}}\ninitFenwick(1);for(int i=0;i<3;i++)add(1,1000000000);assert(rangeSum(1,1)==3000000000LL);',
'segment-tree':'mt19937 rng(77);for(int len=1;len<=25;len++){nums.assign(len,0);initSegment();vector<ll> ref(len,0);for(int t=0;t<100;t++){int idx=rng()%len;ll v=int(rng()%100)-50;ref[idx]=v;update(1,0,len-1,idx,v);int l=rng()%len,r=rng()%len;if(l>r)swap(l,r);ll sum=0;for(int i=l;i<=r;i++)sum+=ref[i];assert(query(1,0,len-1,l,r)==sum);}}nums={};initSegment();\nnums={1000000000,1000000000,1000000000};initSegment();assert(query(1,0,2,0,2)==3000000000LL);update(1,0,2,1,-1000000000);assert(query(1,0,2,0,2)==1000000000LL);',
'euler-tour':'edges={{1,2},{0,3},{0},{1}};eulerTour(0);assert((order==vector<int>{0,1,3,2}));assert(tin[1]==1&&tout[1]==3);assert(tout[0]-tin[0]==4);edges={{}};eulerTour(0);assert(tin[0]==0&&tout[0]==1);',
'lca':'mt19937 rng(88);for(int len=1;len<=45;len++){edges.assign(len,{});for(int v=1;v<len;v++){int p=rng()%v;edges[p].push_back(v);edges[v].push_back(p);}for(int root: {0,len-1}){buildLca(root);for(int a=0;a<len;a++)for(int b=0;b<len;b++){int x=a,y=b;while(depth[x]>depth[y])x=parent[0][x];while(depth[y]>depth[x])y=parent[0][y];while(x!=y){x=parent[0][x];y=parent[0][y];}assert(lca(a,b)==x);}}}\nedges.assign(200000,{});for(int i=1;i<200000;i++){edges[i-1].push_back(i);edges[i].push_back(i-1);}buildLca(0);assert(lca(199999,100000)==100000);assert(lca(199999,0)==0);',
}
# The test harness adds only reference-test dependencies; production snippets remain minimal.
headers='#include <cassert>\n#include <iostream>\n#include <random>\n#include <algorithm>\n#include <numeric>\nusing ll = long long;\n'
def run(item):
 id,body=item
 with tempfile.TemporaryDirectory(prefix='codingtest-cpp-') as tmp:
  source=Path(tmp)/'test.cpp';exe=Path(tmp)/'test'
  source.write_text(headers+(root/'templates'/f'{id}.cpp').read_text()+'\nint main(){\n'+body+'\n}\n')
  standalone=subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-pedantic','-fsyntax-only',str(root/'templates'/f'{id}.cpp')],capture_output=True,text=True,timeout=90)
  if standalone.returncode:return {'id':id,'passed':False,'phase':'standalone-headers','details':standalone.stderr[:3500]}
  result=subprocess.run(['g++','-std=c++17','-O2','-fsanitize=undefined','-fno-sanitize-recover=undefined','-Wall','-Wextra','-pedantic',str(source),'-o',str(exe)],capture_output=True,text=True,timeout=90)
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
report={'compiler':'g++ -std=c++17 -O2 -fsanitize=undefined -fno-sanitize-recover=undefined -Wall -Wextra -pedantic','elapsedSeconds':round(time.time()-start,2),'results':results}
(root/'docs/cpp-results.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
print('Passed',sum(r['passed'] for r in results),'/',len(results))
raise SystemExit(0 if all(r['passed'] for r in results) else 1)
