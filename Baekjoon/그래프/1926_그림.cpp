// visited 대신 grid를 0으로 갱신하면서 하면 더욱 개선 가능

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct node {
    int y, x;
};

int n, m;
vector<vector<int>> grid;
vector<vector<int>> visited;
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};
int ans1 = 0; // 그림의 개수
int ans2 = 0; // 그림의 넓이 MAX

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    grid.resize(n, vector<int>(m));
    visited.resize(n, vector<int>(m, 0));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cin >> grid[r][c];
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (visited[r][c]) continue; // 방문했으면 pass
            if (!grid[r][c]) continue;   // grid 0 이면 pass

            queue<node> q;
            q.push({r, c});
            visited[r][c] = 1;
            int cnt = 0;

            while (!q.empty()) {
                node now = q.front();
                q.pop();
                cnt++; // 꺼낼때마다 cnt +1

                for (int i = 0; i < 4; i++) {
                    int ny = now.y + diry[i];
                    int nx = now.x + dirx[i];
                    if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
                    if (visited[ny][nx]) continue; // 방문했으면 pass
                    if (!grid[ny][nx]) continue;   // grid 0 이면 pass

                    visited[ny][nx] = 1;
                    q.push({ny, nx});
                }
            }

            ans1++;
            ans2 = max(ans2, cnt); // MAX 갱신
        }
    }

    cout << ans1 << "\n";
    cout << ans2 << "\n";
}