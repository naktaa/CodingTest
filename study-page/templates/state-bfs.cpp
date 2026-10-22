#include <queue>
#include <vector>
using namespace std;

struct node {
    int r, c, used;
};

int N, M;
vector<vector<int>> grid;
vector<vector<vector<int>>> dist;
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void stateBfs() { // 1 <= N, M <= 1000, grid[0][0] == 0
    N = grid.size();
    M = grid[0].size();
    dist.assign(N, vector<vector<int>>(M, vector<int>(2, -1)));
    queue<node> q;
    dist[0][0][0] = 0;
    q.push({0, 0, 0});
    while (!q.empty()) {
        node now = q.front();
        q.pop();
        int r = now.r, c = now.c, used = now.used;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
            int next = used + grid[nr][nc];
            if (next > 1 || dist[nr][nc][next] != -1) continue;
            dist[nr][nc][next] = dist[r][c][used] + 1;
            q.push({nr, nc, next});
        }
    }
}
