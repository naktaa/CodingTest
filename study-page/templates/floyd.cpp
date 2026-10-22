#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

const ll INF = 1'000'000'000'000'000'000LL;
vector<vector<ll>> dist;

void initFloyd(int N) {
    dist.assign(N, vector<ll>(N, INF));
    for (int i = 0; i < N; i++) dist[i][i] = 0;
}

void addEdge(int from, int to, int weight) {
    if (weight < dist[from][to]) dist[from][to] = weight;
}

void floyd() {
    int len = dist.size();
    for (int k = 0; k < len; k++) {
        for (int i = 0; i < len; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < len; j++) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
