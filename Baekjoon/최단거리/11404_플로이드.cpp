// 단방향 간선
// 간선이 유일하지 않은 경우도 있음

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
const ll INF = 1e16;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<ll>> table(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) {
        table[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int from, to;
        ll cost;
        cin >> from >> to >> cost;
        table[from - 1][to - 1] = min(table[from - 1][to - 1], cost);
    }

    // 플로이드 워셜
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // if (k == i || k == j) continue;  // 조건 딱히 필요 없음
                ll cmp = table[i][k] + table[k][j];
                table[i][j] = min(table[i][j], cmp);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll output = (table[i][j] == INF) ? 0 : table[i][j];
            cout << output << " ";
        }
        cout << "\n";
    }
}