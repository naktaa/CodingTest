#include <array>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> grid;
vector<vector<array<int, 2>>> dist;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void stateBfs() { // 비어 있지 않은 격자, grid[0][0] == 0
    int n = grid.size();
    int m = grid[0].size();
    dist.assign(n, vector<array<int, 2>>(m, array<int, 2>{-1, -1}));
    queue<array<int, 3>> q;
    dist[0][0][0] = 0;
    q.push({0, 0, 0});
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        int r = now[0], c = now[1], used = now[2];
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            int next = used + grid[nr][nc];
            if (next > 1 || dist[nr][nc][next] != -1) continue;
            dist[nr][nc][next] = dist[r][c][used] + 1;
            q.push({nr, nc, next});
        }
    }
}
