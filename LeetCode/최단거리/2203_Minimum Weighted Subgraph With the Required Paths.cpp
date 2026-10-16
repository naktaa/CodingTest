/*
n <= 1e5, dist <= 1e5
방향성 그래프
필수경로 다익스트라 src1 src2 둘 다 거쳐서 dest에 도착
다익스트라 2번해서 비교하기
필수경로 포함했는지 dest에서 확인 -> parent? flag?
아니면 dist를 2차원으로 관리해서 0: 필수경로 안지남, 1: 필수경로 지남으로 관리
====================================================================================
무조건 한 지점에서 출발해서 경유하는 문제가 아님
각각 출발해서 합쳐지는것도 가능
다익스트라에 src1 src2 같이 넣고 관리?
비트마스킹으로 관리하면서 해보기
====================================================================================
각각 다익스트라 해놓고 '역방향 그래프'를 이용해 dest로부터 모든 정점에 대해 다익스트라
이후 합류지점을 정해서 계산하기
*/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
    using ll = long long;
    const ll INF = 1e12;
    struct edge {
        int to;
        ll dist;
    };
    struct node {
        int to;
        ll dist;
        bool operator<(const node& other) const {
            return dist > other.dist;
        }
    };

    vector<vector<edge>> Edge;
    vector<vector<edge>> ReverseEdge;
    vector<vector<ll>> dist;

    void dijkstra(int start, int idx) {
        priority_queue<node> pq;
        dist[start][idx] = 0;
        pq.push({start, 0});

        while (!pq.empty()) {
            node now = pq.top();
            pq.pop();
            if (now.dist > dist[now.to][idx]) continue;

            if (idx <= 1) {
                for (const auto& next : Edge[now.to]) {
                    ll ndist = now.dist + next.dist;
                    if (ndist >= dist[next.to][idx]) continue;
                    dist[next.to][idx] = ndist;
                    pq.push({next.to, ndist});
                }
            }
            else {
                for (const auto& next : ReverseEdge[now.to]) {
                    ll ndist = now.dist + next.dist;
                    if (ndist >= dist[next.to][idx]) continue;
                    dist[next.to][idx] = ndist;
                    pq.push({next.to, ndist});
                }
            }
        }
    }

public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        Edge.resize(n);
        ReverseEdge.resize(n);
        dist.assign(n, vector<ll>(3, INF));
        for (auto& e : edges) {
            Edge[e[0]].push_back({e[1], e[2]});
            ReverseEdge[e[1]].push_back({e[0], e[2]});
        }

        dijkstra(src1, 0);
        dijkstra(src2, 1);
        dijkstra(dest, 2);

        ll MIN = INF;
        for (int i = 0; i < n; i++) {
            if (dist[i][0] == INF || dist[i][1] == INF || dist[i][2] == INF) continue;

            ll cmp = 0;
            for (const auto& d : dist[i]) {
                cmp += d;
            }
            MIN = min(MIN, cmp);
        }


        MIN = (MIN == INF) ? -1 : MIN;
        return MIN;
    }
};