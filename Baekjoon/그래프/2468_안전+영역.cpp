// N x N 그리드
// 비가 내리면 h 이하 높이의 지점들은 모두 물에 잠김
// 인접한 지역이 하나라도 잠겨있지 않고
// 해당 지역이 잠겨있지 않은 지역 높이 초과여야 잠기지않음
// 그냥 연결요소 구하는 문제임;;

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct node {
    int y, x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    int H = -1; // 가장 높은 높이
    vector<vector<int>> grid(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            H = max(H, grid[i][j]);
        }
    }

    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};
    int ans = 1;
    vector<vector<int>> visited;

    while (--H) {
        visited.assign(N, vector<int>(N, 0)); // 경우의 수마다 초기화
        int cnt = 0;                          // 물에 안잠긴 연결요소 개수

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (grid[r][c] <= H) continue; // 잠긴 지역 pass
                if (visited[r][c]) continue;   // 이미 방문했으면 pass

                queue<node> q;
                q.push({r, c});
                visited[r][c] = 1;

                // 플러드필
                while (!q.empty()) {
                    auto [y, x] = q.front();
                    q.pop();

                    for (int i = 0; i < 4; i++) {
                        int ny = y + diry[i];
                        int nx = x + dirx[i];
                        if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
                        if (grid[ny][nx] <= H) continue;
                        if (visited[ny][nx]) continue;

                        visited[ny][nx] = 1;
                        q.push({ny, nx});
                    }
                }
                cnt++;
            }
        }
        // cout << H << " -> " << cnt << "\n";
        ans = max(ans, cnt);
    }

    cout << ans << "\n";
}