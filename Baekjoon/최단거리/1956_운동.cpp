// 단방향
// 플로이드 워셜

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;
const ll INF = 1e16;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int V, E; // 마을, 도로
    vector<vector<ll>> table;

    cin >> V >> E;
    table.resize(V, vector<ll>(V, INF));
    while (E--) {
        int f, t, d; // 출발, 도착, 거리
        cin >> f >> t >> d;
        table[f - 1][t - 1] = d;
    }
    for (int i = 0; i < V; i++) {
        table[i][i] = 0;
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                ll cmp = table[i][k] + table[k][j];
                table[i][j] = min(table[i][j], cmp);
            }
        }
    }

    ll ans = INF;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) continue;
            ll sum = table[i][j] + table[j][i];
            ans = min(ans, sum);
        }
    }
    ans = (ans < INF) ? ans : -1;
    cout << ans << "\n";
}