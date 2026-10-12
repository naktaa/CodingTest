// 단방향 간선
// 간선이 유일하지 않은 경우도 있음
// 각 최단경로마다 지나온 도시 개수, 경로 출력
// ------------------------------------------------------------------------------------------------
// 플로이드워셜은 다익스트라랑 다르게 parent 설정
// 2차원 -1 로 초기화 하고 경유하는 k의 parent를 따라가게 갱신

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1e8;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> table(n, vector<int>(n, INF));
    vector<vector<int>> parent(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        table[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int from, to;
        int cost;
        cin >> from >> to >> cost;
        if (cost < table[from - 1][to - 1]) {
            table[from - 1][to - 1] = cost;
            parent[from - 1][to - 1] = from - 1;
        }
    }

    // 플로이드 워셜
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int cmp = table[i][k] + table[k][j];
                if (cmp < table[i][j]) {
                    table[i][j] = cmp;
                    parent[i][j] = parent[k][j]; // 경유하는 k --> j 지점 가져옴
                }
            }
        }
    }

    // table 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int output = (table[i][j] == INF) ? 0 : table[i][j];
            cout << output << " ";
        }
        cout << "\n";
    }

    // 경로 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (table[i][j] == INF || i == j) {
                cout << 0 << "\n";
            }
            else {
                vector<int> path;
                for (int now = j; now != -1; now = parent[i][now]) {
                    path.push_back(now);
                }

                reverse(path.begin(), path.end());
                cout << path.size() << " ";
                for (const auto& p : path) {
                    cout << p + 1 << " ";
                }
                cout << "\n";
            }
        }
    }
}
