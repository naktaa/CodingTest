// 공기 청정기 (0,0) 시작, 두 행 차지
// 미세먼지 있는 곳에서 4방향으로 확산
// -- 공기 청정기가 있으면 확산 X
// -- A/5 만큼 확산, 소수점은 버림
// -- 확산되고 그 자리에 A - A/5*확산된개수 만큼 남음
// 공기청정기의 위쪽은 반시계로, 아래쪽은 시계로 순환
// 바람이 불면 방향대로 미세먼지가 한칸씩 이동
// 공기청정기로 들어가면 미세먼지 사라짐
// 순서: 미세먼지 확산 --> 공기청정기 작동
// ------------------------------------------------------------------------
// 2차원 벡터를 0으로 초기화할 때 resize X --> fill로 채워주기
// 역방향으로 미세먼지를 당겨주면 더 간결
/*
    // 1. 위쪽 공기청정기 (반시계) - 바람의 역방향으로 먼지를 당김
    int top_y = air_purifier[0].first;
    // (↓) 왼쪽 열: 위에서 아래로 당김
    for (int y = top_y - 1; y > 0; --y) grid[y][0] = grid[y-1][0];
    // (←) 상단 행: 오른쪽에서 왼쪽으로 당김
    for (int x = 0; x < C - 1; ++x) grid[0][x] = grid[0][x+1];
    // (↑) 오른쪽 열: 아래에서 위로 당김
    for (int y = 0; y < top_y; ++y) grid[y][C-1] = grid[y+1][C-1];
    // (→) 공기청정기 행: 왼쪽에서 오른쪽으로 당김
    for (int x = C - 1; x > 1; --x) grid[top_y][x] = grid[top_y][x-1];
    grid[top_y][1] = 0; // 공기청정기에서 나온 바람은 정화됨

    // 2. 아래쪽 공기청정기 (시계)
    int bot_y = air_purifier[1].first;
    // (↑) 왼쪽 열: 아래에서 위로 당김
    for (int y = bot_y + 1; y < R - 1; ++y) grid[y][0] = grid[y+1][0];
    // (←) 하단 행: 오른쪽에서 왼쪽으로 당김
    for (int x = 0; x < C - 1; ++x) grid[R-1][x] = grid[R-1][x+1];
    // (↓) 오른쪽 열: 위에서 아래로 당김
    for (int y = R - 1; y > bot_y; --y) grid[y][C-1] = grid[y-1][C-1];
    // (→) 공기청정기 행: 왼쪽에서 오른쪽으로 당김
    for (int x = C - 1; x > 1; --x) grid[bot_y][x] = grid[bot_y][x-1];
    grid[bot_y][1] = 0;
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};

int main() {
    int R, C, T;                   // 행, 열, 시간
    vector<vector<int>> grid;      // 구역
    vector<vector<int>> grid_temp; // 계산할 때 임시 구역
    vector<pair<int, int>> AIR;    // 공기청정기 좌표 저장
    cin >> R >> C >> T;
    grid.resize(R, vector<int>(C));
    grid_temp.resize(R, vector<int>(C));
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            cin >> grid[r][c];
            if (grid[r][c] == -1) AIR.push_back({r, c}); // 위 -> 아래 순으로 저장
        }
    }

    // 시뮬레이션 시작
    int TIME = 0;
    while (TIME++ < T) {
        for (auto& temp : grid_temp) {
            fill(temp.begin(), temp.end(), 0); // 임시 구역 1초마다 0으로 초기화
        }
        for (auto air : AIR) {
            grid_temp[air.first][air.second] = -1;
        }
        // 미세먼지 확산
        for (int y = 0; y < R; y++) {
            for (int x = 0; x < C; x++) {
                if (grid[y][x] <= 0) continue; // 미세먼지가 없거나 공기청정기면 pass
                int spread = grid[y][x] / 5;   // 확산되는 양
                int cnt = 0;                   // 확산된 횟수

                // 4방향 확산
                for (int i = 0; i < 4; i++) {
                    int ny = y + diry[i];
                    int nx = x + dirx[i];
                    if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue; // 구역 벗어나면 pass
                    if (grid[ny][nx] == -1) continue;                     // 공기청정기면 pass
                    grid_temp[ny][nx] += spread;
                    cnt++;
                }
                grid_temp[y][x] += (grid[y][x] - spread * cnt); // 확산 끝나고 그 자리에 남는 양
            }
        }

        // 공기청정기 작동
        for (int i = 0; i < 2; i++) {
            auto air = AIR[i];
            int DIR = 0;  // 현재 순환 방향
            int prev = 0; // 이전 구역 미세먼지 양
            int next;     // 다음 구역으로

            while (1) {
                int ny = air.first + diry[DIR % 4];
                int nx = air.second + dirx[DIR % 4];

                // 공기청정기 행보다 위 or 아래면 방향 전환
                if (i == 0) {
                    if (ny > AIR[i].first) {
                        DIR += 3;
                        continue;
                    }
                }
                else {
                    if (ny < AIR[i].first) {
                        DIR += 1;
                        continue;
                    }
                }
                // 구역 벗어나면 방향 전환
                if (ny < 0 || nx < 0 || ny >= R || nx >= C) {
                    if (i == 0) {
                        DIR += 3;
                    }
                    else {
                        DIR += 1;
                    }
                    continue;
                }
                if (grid_temp[ny][nx] == -1) break; // 공기청정기로 돌아오면 break

                next = grid_temp[ny][nx];
                grid_temp[ny][nx] = prev;
                prev = next;
                air = {ny, nx};
            }
        }

        grid = grid_temp; // 계산 끝난 임시구역 grid로 복사
    }

    int ans = 0;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] <= 0) continue;
            ans += grid[r][c];
        }
    }
    cout << ans << "\n";
}


/*
for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
        cout << grid_temp[r][c] << " ";
    }
    cout << "\n";
}
cout << "\n";
*/

// cout << "(" << ny << ", " << nx << ") = " << prev << ", " << "DIR= " << DIR << "\n";
