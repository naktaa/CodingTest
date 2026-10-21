#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;
vector<vector<pair<int, long long>>> edges;
vector<long long> dist;

void dijkstra(int start) {
    dist.assign(edges.size(), INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [cost, now] = pq.top();
        pq.pop();
        if (cost != dist[now]) continue;
        for (const auto& [next, weight] : edges[now]) {
            long long nextCost = cost + weight;
            if (nextCost >= dist[next]) continue;
            dist[next] = nextCost;
            pq.push({nextCost, next});
        }
    }
}
