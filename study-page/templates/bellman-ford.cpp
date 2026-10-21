#include <array>
#include <limits>
#include <vector>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;
int n;
vector<array<long long, 3>> edges; // from, to, weight
vector<long long> dist;

bool bellmanFord(int start) {
    dist.assign(n, INF);
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        bool updated = false;
        for (const auto& edge : edges) {
            int from = static_cast<int>(edge[0]);
            int to = static_cast<int>(edge[1]);
            if (dist[from] == INF) continue;
            long long next = dist[from] + edge[2];
            if (next >= dist[to]) continue;
            dist[to] = next;
            updated = true;
            if (i == n - 1) return false;
        }
        if (!updated) return true;
    }
    return true;
}
