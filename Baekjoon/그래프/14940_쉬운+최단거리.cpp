// 시작점부터 플러드필 하면서 저장
// 0: 갈 수 없는 땅  |  1: 갈 수 있는 땅  |  2: 목표지점
// 갈 수 없는 땅 0 유지
// 갈 수 있는 땅은 grid 바꿔가며 갱신 1인데 갱신 안됐으면 -1로 바꿔서 출력

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct coord {
    int y, x;
};
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;                 // n x m
    vector<vector<int>> grid; // 지도
    coord target;             // 목표지점

    // 입력
    cin >> n >> m;
    grid.resize(n, vector<int>(m));
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            cin >> grid[y][x];
            if (grid[y][x] == 1)
                grid[y][x] = -1;
            else if (grid[y][x] == 2)
                target = {y, x};
        }
    }

    // 플러드필 시작
    queue<coord> q;
    q.push(target);
    grid[target.y][target.x] = 0;

    while (!q.empty()) {
        coord now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + diry[i];
            int nx = now.x + dirx[i];

            if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
            if (grid[ny][nx] != -1) continue;

            grid[ny][nx] = grid[now.y][now.x] + 1;
            q.push({ny, nx});
        }
    }

    // 출력
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            // cout << ((grid[y][x] != 1) ? grid[y][x] : -1) << " ";
            cout << grid[y][x] << " ";
        }
        cout << "\n";
    }
}