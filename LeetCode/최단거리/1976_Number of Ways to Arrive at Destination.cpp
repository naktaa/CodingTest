/*
n <= 200
0 -> n-1 까지 최단거리의 개수
mod 10e9 + 7
그냥 parent 배열 여러개 저장해서 다익스트라 해놓고 계산하기 -> 계산할 때 dp 안하면 타임리밋
다익스트라 진행하면서 바로 계산해서 갱신하는걸로
*/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
    using ll = long long;
    const ll INF = 1e16;
    const int MOD = 1e9 + 7;
    struct edge {
        int to;
        ll dist;
        bool operator<(const edge other) const {
            return dist > other.dist;
        }
    };
    struct node {
        ll dist;
        int cnt;
    };

    vector<vector<edge>> edges;
    vector<node> nodes;

    void dijkstra() {
        priority_queue<edge> pq;
        nodes[0] = {0, 1};
        pq.push({0, 0});

        while (!pq.empty()) {
            edge now = pq.top();
            pq.pop();
            if (now.dist > nodes[now.to].dist) continue;

            for (const auto& next : edges[now.to]) {
                ll ndist = now.dist + next.dist;
                if (ndist >= nodes[next.to].dist) {
                    if (ndist == nodes[next.to].dist) {
                        nodes[next.to].cnt += nodes[now.to].cnt;
                        nodes[next.to].cnt %= MOD;
                    }
                    continue;
                }

                nodes[next.to] = {ndist, nodes[now.to].cnt};
                pq.push({next.to, ndist});
            }
        }
    }

public:
    int countPaths(int n, vector<vector<int>>& roads) {
        edges.resize(n);
        nodes.assign(n, {INF, 0});
        for (const auto& road : roads) {
            edges[road[0]].push_back({road[1], road[2]});
            edges[road[1]].push_back({road[0], road[2]});
        }

        dijkstra();
        return nodes[n - 1].cnt;
    }
};