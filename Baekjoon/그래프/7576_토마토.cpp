// 하루 뒤 익은 토마토 4방향 익어짐
// 모두 다 익는 최소 일수
// 1: 익은, 0: 익지않은, -1: 토마토 없음
// 다 익지않으면 -1 출력

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int N, M;                 // N x M
    vector<vector<int>> grid; // 창고
    int ans = 0;              // 답
    int cnt = 0;              // 토마토 수
    int cmp = 0;              // 토마토 수 비교용
    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};

    cin >> M >> N;
    grid.resize(N, vector<int>(M));
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            cin >> grid[y][x];
            if (grid[y][x] >= 0) cnt++;
        }
    }

    // bfs 시작
    queue<pair<int, int>> q;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (grid[y][x] <= 0) continue;
            q.push({y, x});
        }
    }

    while (!q.empty()) {
        auto now = q.front(); // auto [y,x] = q.front(); -> 구조적 바인딩으로 first, second 대신 편하게 사용 가능
        q.pop();
        cmp++;
        ans = max(ans, grid[now.first][now.second]);

        for (int i = 0; i < 4; i++) {
            int ny = now.first + diry[i];
            int nx = now.second + dirx[i];
            if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue; // 범위 벗어나면 pass
            if (grid[ny][nx] != 0) continue;                      // 익었거나 없으면 pass

            grid[ny][nx] = grid[now.first][now.second] + 1;
            q.push({ny, nx});
        }
    }

    cout << ((cnt == cmp) ? ans - 1 : -1) << "\n";
}