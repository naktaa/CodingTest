// 플러드필로 접근
// bfs 대신 dfs 재귀로 하면 조금 더 최적화 가능
// visited 대신 grid를 직접 수정하며 탐색 가능

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};

int main() {
    int T;
    cin >> T;
    int tc = 0;
    while (tc++ < T) {
        int M, N, K;                 // 가로, 세로, 위치개수
        vector<vector<int>> grid;    // 배추밭
        vector<vector<int>> visited; // 탐색 여부
        int ans = 0;                 // 답
        cin >> M >> N >> K;
        grid.assign(N, vector<int>(M, 0));
        visited.assign(N, vector<int>(M, 0));

        // 배추 심어진 위치
        for (int i = 0; i < K; i++) {
            int X, Y;
            cin >> X >> Y;
            grid[Y][X] = 1;
        }

        // 탐색
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (grid[y][x] == 0 || visited[y][x] == 1) continue;
                ans++;
                queue<pair<int, int>> q;
                q.push({y, x});
                visited[y][x] = 1;

                while (!q.empty()) {
                    pair<int, int> now = q.front();
                    q.pop();

                    for (int i = 0; i < 4; i++) {
                        int ny = now.first + diry[i];
                        int nx = now.second + dirx[i];
                        if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
                        if (grid[ny][nx] == 0 || visited[ny][nx] == 1) continue;
                        visited[ny][nx] = 1;
                        q.push({ny, nx});
                    }
                }
            }
        }

        cout << ans << "\n";
    }
}