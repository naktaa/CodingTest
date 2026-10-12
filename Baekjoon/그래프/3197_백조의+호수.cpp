// 하루 지날때마다 bfs 하기
// bfs 하고 막힌 X 지점들
// 중간에 백조없이 물만 있는 지점들도 생각해서 얼음 녹이기
// 백조가 탐색한 공간은 저장해서 재탐색 안하기
// 백조 bfs --> 얼음 녹이기 순서로
// 백조 2개 다 탐색하면서 1 2 로 나눠서 visited하다가 서로 만날 때 조건 걸고 break
// 녹일 얼음 미리 구해놓고 녹인 다음에 다음 녹일 얼음 다시 넣어줌
// ---------------------------------------------------------------------------------------------------
// set 쓰지 말고 오늘 다음날 큐 각각 만들어서 4개 큐로 관리
// set은 시간복잡도 높은거 생각

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
using namespace std;
using PR = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int R, C;
    vector<string> grid;
    cin >> R >> C;
    for (int r = 0; r < R; r++) {
        string line;
        cin >> line;
        grid.push_back(line);
    }

    vector<vector<int>> visited(R, vector<int>(C, 0)); // 백조가 방문한 곳 저장
    set<PR> ices_next;                                 // 다음날 녹을 빙판
    set<PR> swan1_next;                                // swan1 다음 지점
    set<PR> swan2_next;                                // swan2 다음 지점
    vector<PR> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int swan_flag = 0;
    int ans = 0; // 며칠


    // 초기 조건 세팅
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == 'L') {
                if (!swan_flag) {
                    swan1_next.insert({r, c});
                    swan_flag = 1;
                }
                else {
                    swan2_next.insert({r, c});
                }
            }
            else if (grid[r][c] == 'X') {
                for (const auto& dir : dirs) {
                    int ny = r + dir.second;
                    int nx = c + dir.first;
                    if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
                    // 물, 백조에 인접하면 ices에 추가
                    if (grid[ny][nx] == '.' || grid[ny][nx] == 'L') {
                        ices_next.insert({r, c});
                        break;
                    }
                }
            }
        }
    }


    while (1) {
        queue<PR> q;
        set<PR> temp; // 복사용 임시 set

        // swan 1 탐색
        temp = swan1_next;
        swan1_next.clear();
        for (const auto& swan : temp) {
            if (visited[swan.first][swan.second] == 1) continue; // 이미 꺼내서 탐색했으면 pass
            q.push({swan.first, swan.second});
            visited[swan.first][swan.second] = 1;

            while (!q.empty()) {
                PR now = q.front();
                q.pop();

                for (const auto& dir : dirs) {
                    int ny = now.first + dir.first;
                    int nx = now.second + dir.second;

                    if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
                    if (visited[ny][nx] == 1) continue;
                    if (grid[ny][nx] == 'X') {
                        swan1_next.insert({ny, nx});
                        continue;
                    }

                    visited[ny][nx] = 1;
                    q.push({ny, nx});
                }
            }
        }

        // swan 2 탐색
        temp = swan2_next;
        swan2_next.clear();
        for (const auto& swan : temp) {
            // swan 1 이 방문한 곳이면 정답 출력
            if (visited[swan.first][swan.second] == 1) {
                cout << ans << "\n";
                return 0;
            }
            if (visited[swan.first][swan.second] == 2) continue; // 이미 꺼내서 탐색했으면 pass
            q.push({swan.first, swan.second});
            visited[swan.first][swan.second] = 2;

            while (!q.empty()) {
                PR now = q.front();
                q.pop();

                for (const auto& dir : dirs) {
                    int ny = now.first + dir.first;
                    int nx = now.second + dir.second;

                    if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
                    if (visited[ny][nx] == 2) continue;
                    if (grid[ny][nx] == 'X') {
                        swan2_next.insert({ny, nx});
                        continue;
                    }

                    visited[ny][nx] = 2;
                    q.push({ny, nx});
                }
            }
        }

        // ice 녹이기
        temp = ices_next;
        ices_next.clear();
        for (const auto& ice : temp) {
            grid[ice.first][ice.second] = '.';
        }
        for (const auto& ice : temp) {
            for (const auto& dir : dirs) {
                int ny = ice.first + dir.first;
                int nx = ice.second + dir.second;

                if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
                if (grid[ny][nx] == 'X') ices_next.insert({ny, nx});
            }
        }

        ans++;
    }
}