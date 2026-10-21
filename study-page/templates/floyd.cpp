#include <algorithm>
#include <limits>
#include <vector>
using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;
vector<vector<long long>> dist;

void initFloyd(int n) {
    dist.assign(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
}

void addEdge(int from, int to, long long weight) {
    dist[from][to] = min(dist[from][to], weight);
}

void floyd() {
    int n = dist.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
