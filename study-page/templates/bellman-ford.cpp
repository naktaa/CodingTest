#include <vector>
using namespace std;
using ll = long long;

const ll INF = 1'000'000'000'000'000'000LL;

struct edge {
    int from, to, weight;
};

int N;
vector<edge> edges;
vector<ll> dist;

bool bellmanFord(int start) { // N <= 500, 간선 <= 5000, |weight| <= 10^9
    dist.assign(N, INF);
    dist[start] = 0;
    for (int i = 0; i < N; i++) {
        bool updated = false;
        for (edge now : edges) {
            if (dist[now.from] == INF) continue;
            ll next = dist[now.from] + now.weight;
            if (next >= dist[now.to]) continue;
            dist[now.to] = next;
            updated = true;
            if (i == N - 1) return false;
        }
        if (!updated) return true;
    }
    return true;
}
