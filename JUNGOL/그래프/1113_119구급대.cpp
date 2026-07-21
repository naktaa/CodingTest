#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using pr = pair<int, int>;

int main() {
    int M, N, m, n;
    vector<vector<int>> grid;

    cin >> M >> N >> m >> n;
    grid.assign(M, vector<int>(N, 0));
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            cin >> grid[y][x];
        }
    }

    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};
    vector<vector<int>> visited(M, vector<int>(N, -1));
    queue<pr> q;
    q.push({0, 0});

    while (!q.empty()) {
        pr now = q.front();
        q.pop();
        if (now.first == m && now.second == n) break;

        for (int i = 0; i < 4; i++) {
            int cnt = 0;
            while (1) {
                cnt++;
                int ny = now.first + diry[i] * cnt;
                int nx = now.second + dirx[i] * cnt;

                if (ny < 0 || nx < 0 || ny >= M || nx >= N) break;
                if (grid[ny][nx] == 0) break;
                if (ny == 0 && nx == 0) break;
                if (visited[ny][nx] != -1) continue;
                q.push({ny, nx});
                visited[ny][nx] = visited[now.first][now.second] + 1;
            }
        }
    }

    cout << visited[m][n];
}