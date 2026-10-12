// ================================================================================
// 한 방향으로 가는 경우는 dfs로 하기
// dp로 state 관리하면서 cnt 세기

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
using pr = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<int>> grid;
    vector<vector<int>> visited;
    int dirr[] = {-1, 0, 1, 0};
    int dirc[] = {0, 1, 0, -1};
    int ans = 0;

    cin >> N >> M;
    grid.resize(N, vector<int>(M));
    visited.resize(N, vector<int>(M, 0));
    for (int r = 0; r < N; r++) {
        string s;
        cin >> s;
        for (int c = 0; c < M; c++) {
            if (s[c] == 'U') {
                grid[r][c] = 0;
            }
            else if (s[c] == 'R') {
                grid[r][c] = 1;
            }
            else if (s[c] == 'D') {
                grid[r][c] = 2;
            }
            else if (s[c] == 'L') {
                grid[r][c] = 3;
            }
        }
    }

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (visited[r][c]) continue;
            // cout << r << ", " << c << "  |  ";

            vector<pr> path;
            queue<pr> q;
            q.push({r, c});
            int cnt = 0;

            while (!q.empty()) {
                pr now = q.front();
                q.pop();
                visited[now.first][now.second] = 1;
                path.push_back({now.first, now.second});
                cnt++;

                int next_dir = grid[now.first][now.second];
                int nr = now.first + dirr[next_dir];
                int nc = now.second + dirc[next_dir];

                if (nr < 0 || nc < 0 || nr >= N || nc >= M) {
                    ans += cnt;
                    // cout << nr << ", " << nc << ": cnt = " << cnt << "\n";
                    // for (int i = 0; i < N; i++) {
                    //     for (int j = 0; j < M; j++) {
                    //         cout << visited[i][j] << " ";
                    //     }
                    //     cout << "\n";
                    // }

                    for (const auto& p : path) {
                        grid[p.first][p.second] = 4;
                    }
                    break;
                }

                if (visited[nr][nc]) {
                    if (grid[nr][nc] == 4) {
                        ans += cnt;
                        // cout << nr << ", " << nc << ": cnt = " << cnt << "\n";
                        for (const auto& p : path) {
                            grid[p.first][p.second] = 4;
                        }
                        break;
                    }
                    else if (grid[nr][nc] == -1) {
                        for (const auto& p : path) {
                            grid[p.first][p.second] = -1;
                        }
                        break;
                    }
                    else {
                        for (const auto& p : path) {
                            grid[p.first][p.second] = -1;
                        }
                        break;
                    }
                }
                q.push({nr, nc});
            }
        }
    }

    cout << ans << "\n";
}