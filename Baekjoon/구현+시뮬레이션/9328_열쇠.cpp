// '.' 빈 공간 -> 52  |  '*' 벽 -> -1  |  '$' 문서 -> 100
// 대문자: 문 -> 26 ~ 51   |  소문자: 문을 열 수 있는 열쇠 -> 0 ~ 25
// queue에 넣어주면서 열쇠 있는지 확인
// 열쇠가 있다면 바로 큐에 넣고 없으면 좌표 기록해놓고 대기
// ==========================================================================================
// 벡터 초기화 신경써주기 --> 자주 초기화 해줘야되면 assign으로
// 테두리 신경써야되면 바깥에 1줄 패딩 해주는것도 좋음

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;

struct coord {
    int y, x;
};

int h, w;                    // 높이, 너비
vector<vector<int>> grid;    // 맵
vector<int> key;             // 가진 열쇠
vector<vector<coord>> door;  // 문 좌표
vector<vector<int>> visited; // 방문 여부
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};
int ans = 0;

void init() {
    grid.clear();
    key.assign(26, 0);
    door.assign(26, vector<coord>());
    visited.clear();
    ans = 0;
}

void input() {
    cin >> h >> w;
    grid.resize(h, vector<int>(w));
    visited.resize(h, vector<int>(w, 0));
    for (int y = 0; y < h; y++) {
        string row;
        cin >> row;
        for (int x = 0; x < w; x++) {
            if (row[x] >= 'A' && row[x] <= 'Z') {
                grid[y][x] = row[x] - 'A' + 26;
            }
            else if (row[x] >= 'a' && row[x] <= 'z') {
                grid[y][x] = row[x] - 'a';
            }
            else if (row[x] == '*') {
                grid[y][x] = -1;
            }
            else if (row[x] == '.') {
                grid[y][x] = 52;
            }
            else if (row[x] == '$') {
                grid[y][x] = 100;
            }
        }
    }

    string keys;
    cin >> keys;
    if (keys[0] == '0') return;
    for (const auto& k : keys) {
        key[k - 'a'] = 1;
    }
}

void solution() {
    queue<coord> q;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (!(y == 0 || x == 0 || y == h - 1 || x == w - 1)) continue;
            if (grid[y][x] == -1)
                continue; // 벽이거나 방문했으면 pass
            else if (grid[y][x] >= 26 && grid[y][x] < 52) {
                if (!key[grid[y][x] - 26]) {
                    door[grid[y][x] - 26].push_back({y, x});
                    visited[y][x] = 1;
                    continue;
                }
            }
            else if (grid[y][x] >= 0 && grid[y][x] < 26) {
                if (!key[grid[y][x]]) {
                    for (const auto& d : door[grid[y][x]]) {
                        q.push({d.y, d.x});
                    }
                }
                key[grid[y][x]] = 1;
            }

            visited[y][x] = 1;
            q.push({y, x});
        }
    }

    while (!q.empty()) {
        coord now = q.front();
        q.pop();
        if (grid[now.y][now.x] == 100) ans++;

        for (int i = 0; i < 4; i++) {
            int ny = now.y + diry[i];
            int nx = now.x + dirx[i];

            if (ny < 0 || nx < 0 || ny >= h || nx >= w) continue;
            if (grid[ny][nx] == -1) continue;
            if (visited[ny][nx]) continue;

            if (grid[ny][nx] >= 26 && grid[ny][nx] < 52) {
                if (!key[grid[ny][nx] - 26]) {
                    door[grid[ny][nx] - 26].push_back({ny, nx});
                    visited[ny][nx] = 1;
                    continue;
                }
            }
            else if (grid[ny][nx] >= 0 && grid[ny][nx] < 26) {
                if (!key[grid[ny][nx]]) {
                    for (const auto& d : door[grid[ny][nx]]) {
                        q.push({d.y, d.x});
                    }
                }
                key[grid[ny][nx]] = 1;
            }

            visited[ny][nx] = 1;
            q.push({ny, nx});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        init();
        input();
        solution();
        cout << ans << "\n";
    }
}