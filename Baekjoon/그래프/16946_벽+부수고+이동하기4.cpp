// 0인 부분들을 플러드필 하면서 크기가 몇인지 구하기
// 플러드필 하면서 인접한 1인 grid의 좌표들을 저장해서 크기만큼 더해주기?
// 0 빈곳  |  1 벽  |  2 bfs 끝난곳
// ====================================================================================================
// 플러드필 하면서 다 set에 넣으면 오버헤드 커짐
// 미리 0인 부분들을 그룹화 해놓고 1일때 인접 그룹들을 더해서 하면 최적화 가능

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <set>
using namespace std;
using pr = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<int>> grid; // 맵
    vector<vector<int>> cnt;  // 이동할 수 있는 칸 개수
    int dirr[] = {0, 1, 0, -1};
    int dirc[] = {1, 0, -1, 0};

    cin >> N >> M;
    grid.resize(N, vector<int>(M));
    cnt.resize(N, vector<int>(M, 0));
    for (int r = 0; r < N; r++) {
        string s;
        cin >> s;
        for (int c = 0; c < M; c++) {
            grid[r][c] = s[c] - '0';
        }
    }

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (grid[r][c] == 1) {
                cnt[r][c]++;
            }
            else if (grid[r][c] == 0) {
                set<pr> COORD; // 인접한 1의 좌표들
                int size = 0;  // 0 플러드필의 크기

                queue<pr> q;
                grid[r][c] = 2;
                q.push({r, c});

                while (!q.empty()) {
                    pr now = q.front();
                    q.pop();
                    size++;

                    for (int i = 0; i < 4; i++) {
                        int nr = now.first + dirr[i];
                        int nc = now.second + dirc[i];
                        if (nr < 0 || nc < 0 || nr >= N || nc >= M) continue;

                        if (grid[nr][nc] == 1) {
                            COORD.insert({nr, nc});
                        }
                        else if (grid[nr][nc] == 0) {
                            grid[nr][nc] = 2;
                            q.push({nr, nc});
                        }
                    }
                }

                for (const auto& coord : COORD) {
                    cnt[coord.first][coord.second] += size;
                }
            }
        }
    }

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            cout << cnt[r][c] % 10;
        }
        cout << "\n";
    }
}