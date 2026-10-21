#include <deque>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

vector<vector<pair<int, int>>> edges; // next, weight (0 or 1)
vector<int> dist;

void zeroOneBfs(int start) {
    dist.assign(edges.size(), numeric_limits<int>::max() / 4);
    deque<pair<int, int>> dq; // distance, vertex
    dist[start] = 0;
    dq.push_front({0, start});
    while (!dq.empty()) {
        auto [cost, now] = dq.front();
        dq.pop_front();
        if (cost != dist[now]) continue;
        for (const auto& [next, weight] : edges[now]) {
            int nextCost = cost + weight;
            if (nextCost >= dist[next]) continue;
            dist[next] = nextCost;
            if (weight == 0) dq.push_front({nextCost, next});
            else dq.push_back({nextCost, next});
        }
    }
}
