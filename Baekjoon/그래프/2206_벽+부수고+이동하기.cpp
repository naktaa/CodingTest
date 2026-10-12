// N x M 그리드
// 0 이동가능  1 벽
// 벽은 1개까지만 제거 가능 최단거리 구하기
// visited를 3차원으로 벽 부순 횟수까지 추가해서 관리
// dist가 더 크면 push X

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 21e8;

struct node {
    int y, x, cnt, dist; // 좌표, 부순 횟수, 거리
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> grid(N, vector<int>(M));
    vector<vector<vector<int>>> dist(N, vector<vector<int>>(M, vector<int>(2, INF))); // N x M x 2
    for (int r = 0; r < N; r++) {
        string line;
        cin >> line;
        for (int c = 0; c < M; c++) {
            grid[r][c] = line[c] - '0';
        }
    }

    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};
    queue<node> q;
    q.push({0, 0, 0, 1});
    dist[0][0][0] = 1;

    while (!q.empty()) {
        node now = q.front();
        q.pop();
        // cout << "(" << now.y << ", " << now.x << ") -> dist = " << now.dist << ", cnt = " << now.cnt << "\n";
        if (now.dist > dist[now.y][now.x][now.cnt]) continue; // 더 최단거리로 갱신됐으면 pass


        for (int i = 0; i < 4; i++) {
            int ny = now.y + diry[i];
            int nx = now.x + dirx[i];
            int ncnt = now.cnt;
            int ndist = now.dist + 1;


            if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue; // grid 범위 체크
            // 다음 위치가 벽일 때
            if (grid[ny][nx]) {
                if (ncnt)
                    continue; // 부순횟수 1
                else
                    ncnt++; // 부순횟수 0
            }
            if (ndist >= dist[ny][nx][ncnt]) continue;
            dist[ny][nx][ncnt] = ndist;
            q.push({ny, nx, ncnt, ndist});
        }
    }

    int ans = min(dist[N - 1][M - 1][0], dist[N - 1][M - 1][1]);
    if (ans == INF) ans = -1;
    cout << ans << "\n";
}