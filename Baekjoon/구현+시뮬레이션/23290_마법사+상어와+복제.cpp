// 4x4
// 상어, 물고기냄새, 범위밖은 못감
// 진행 못하면 반시계 45도 회전
// 상어는 3칸 연속이동 상하좌우
// 지나가는 길에 물고기 있으면 제외시키고 냄새가 남음
// 냄새는 2번 지나면 사라짐
// 가장 많은 물고기를 제외할 수 있는 방향으로 가고 여러개라면 사전순 --> 변환한 숫자가 작을수록 우선순위 --> 우 하 좌 상
// 물고기 이동  -->  상어 이동  -->  냄새 남기기  -->  복제

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct coord {
    int y, x;
};

vector<vector<vector<int>>> grid(4, vector<vector<int>>(4, vector<int>(8, 0)));
vector<vector<vector<int>>> grid_copy(4, vector<vector<int>>(4, vector<int>(8, 0)));
vector<vector<int>> smell(4, vector<int>(4, 0)); // 0: 빈곳
vector<vector<int>> visited(4, vector<int>(4, 0));

int M, S;    // 물고기, 연습 수
coord shark; // 상어 위치
int diry[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dirx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dirr[] = {0, 1, 0, -1};
int dirc[] = {1, 0, -1, 0};
int MAX = -1;                  // 상어가 제거할 물고기 최대 수
vector<int> dir_shark(3, -1);  // 상어가 움직이는 방향
vector<int> dir_record(3, -1); // 방향 기록
int ans = 0;

void dfs(int y, int x, int depth, int cnt) {
    if (y < 0 || x < 0 || y >= 4 || x >= 4) return;
    if (depth >= 3) {
        if (cnt >= MAX) {
            MAX = cnt;
            dir_shark = dir_record;
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        int ny = y + dirr[i];
        int nx = x + dirc[i];
        if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) continue;

        dir_record[depth] = i;
        int sum = 0;

        if (!visited[ny][nx]) {
            for (int j = 0; j < 8; j++) {

                sum += grid[ny][nx][j];
            }
        }

        visited[ny][nx]++;
        dfs(ny, nx, depth + 1, cnt + sum);
        visited[ny][nx]--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> M >> S;
    for (int i = 0; i < M; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        grid[x - 1][y - 1][d - 1]++;
    }
    cin >> shark.y >> shark.x;
    shark.y--;
    shark.x--;

    while (S--) {
        // 물고기 이동
        grid_copy = grid;

        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                for (int d = 0; d < 8; d++) {
                    if (!grid_copy[y][x][d]) continue;

                    int rotate_cnt = 8;
                    int can_go = 0;
                    int fish_cnt = grid_copy[y][x][d];
                    int ny, nx, nd = d;

                    while (rotate_cnt--) {
                        ny = y + diry[nd];
                        nx = x + dirx[nd];

                        // 해당 방향의 물고기 없으면 회전
                        if (ny < 0 || nx < 0 || ny >= 4 || nx >= 4) {
                            nd = (nd + 7) % 8;
                            continue;
                        }
                        // 상어 있거나 냄새 남아있으면 회전
                        if ((ny == shark.y && nx == shark.x) || smell[ny][nx]) {
                            nd = (nd + 7) % 8;
                            continue;
                        }
                        can_go = 1;
                        break;
                    }

                    if (!can_go) continue;
                    grid[y][x][d] -= fish_cnt;
                    grid[ny][nx][nd] += fish_cnt;
                }
            }
        }

        // 냄새 감소
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (smell[y][x] > 0) smell[y][x]--;
            }
        }

        // 상어 이동
        MAX = -1;
        for (int i = 0; i < 4; i++) {
            fill(visited[i].begin(), visited[i].end(), 0);
        }
        dfs(shark.y, shark.x, 0, 0);
        int ny = shark.y, nx = shark.x;
        for (int i = 0; i < 3; i++) {
            ny += dirr[dir_shark[i]];
            nx += dirc[dir_shark[i]];

            for (int d = 0; d < 8; d++) {
                if (grid[ny][nx][d]) smell[ny][nx] = 2; // 물고기 있었으면 냄새 남기기
                grid[ny][nx][d] = 0;
            }
        }
        shark = {ny, nx}; // 이동한 위치로 옮겨주기

        // 복제 마법
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                for (int d = 0; d < 8; d++) {
                    grid[y][x][d] += grid_copy[y][x][d];
                }
            }
        }
    }

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            for (int d = 0; d < 8; d++) {
                ans += grid[y][x][d];
            }
        }
    }

    // for (int d = 0; d < 8; d++) {
    //     cout << "\n======================================\n";
    //     for (int y = 0; y < 4; y++) {
    //         for (int x = 0; x < 4; x++) {
    //             cout << grid[y][x][d] << " ";
    //         }
    //         cout << "\n";
    //     }
    // }

    cout << ans << "\n";
}