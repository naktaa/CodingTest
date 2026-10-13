/*
단방향 그래프  |  2 <= n <= 100 | dist <= 10e4
경로 없으면 -1
경로를 최대 k번 노드 거쳐서 최단거리 -> k + 1 개 이하로 edge 사용
몇 번 사용해왔는지 다익스트라하면서 기록
단순하게 cnt로 기록하지 말고 dist에서 cnt 관리
======================================================================
다익스트라는 pq에서 꺼낸 순간 최단거리임이 보장됨
dst이면 바로 return 가능
*/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
    struct node {
        int to, dist, cnt;
        bool operator<(const node& other) const {
            return dist > other.dist;
        }
    };
    struct edge {
        int to, dist;
    };
    const int INF = 21e8;

public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<edge>> edges(n);
        for (const auto& flight : flights) {
            edges[flight[0]].push_back({flight[1], flight[2]});
        }

        vector<vector<int>> dist(n, vector<int>(k + 2, INF));
        dist[src][0] = 0;
        priority_queue<node> pq;
        pq.push({src, 0, 0});

        while (!pq.empty()) {
            node now = pq.top();
            pq.pop();
            if (now.dist > dist[now.to][now.cnt]) continue;
            // 처음 꺼낸 dst는 최소 비용이 보장됨
            if (now.to == dst) return now.dist;
            if (now.cnt == k + 1) continue;

            for (const auto& next : edges[now.to]) {
                int ndist = now.dist + next.dist;
                int ncnt = now.cnt + 1;
                if (ndist >= dist[next.to][ncnt]) continue;

                dist[next.to][ncnt] = ndist;
                pq.push({next.to, ndist, ncnt});
            }
        }

        int ans = INF;
        for (const auto& dist : dist[dst]) {
            ans = min(ans, dist);
        }
        ans = (ans == INF) ? -1 : ans;
        return ans;
    }
};