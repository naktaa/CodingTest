#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main() {
    int N, M;                 // N x M
    vector<vector<int>> grid; // 미로
    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};

    cin >> N >> M;
    grid.resize(N, vector<int>(M, 0));
    for (int y = 0; y < N; y++) {
        string num;
        cin >> num;
        for (int x = 0; x < M; x++) {
            grid[y][x] = num[x] - '0';
        }
    }

    // bfs 시작
    vector<vector<int>> visited(N, vector<int>(M, 0)); // 방문 여부 및 칸 수 저장
    queue<pair<int, int>> q;
    visited[0][0] = 1;
    q.push({0, 0});

    while (!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.first + diry[i];
            int nx = now.second + dirx[i];
            if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue; // 범위 벗어나면 pass
            if (visited[ny][nx] > 0) continue;                    // 이미 방문했으면 pass
            if (!grid[ny][nx]) continue;                          // 미로 벽 pass

            visited[ny][nx] = visited[now.first][now.second] + 1;
            q.push({ny, nx});
        }
    }

    cout << visited[N - 1][M - 1] << "\n";
}