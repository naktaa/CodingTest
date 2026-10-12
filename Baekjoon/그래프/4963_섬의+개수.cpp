// 테스트케이스마다 단순하게 resize로 사이즈 조절 불가능

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct coord {
    int y, x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int w, h;
    vector<vector<int>> grid;
    int diry[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dirx[] = {0, 1, 1, 1, 0, -1, -1, -1};

    while (1) {
        cin >> w >> h;
        if (w == 0 || h == 0) return 0;

        grid.assign(h, vector<int>(w, 0));
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                cin >> grid[y][x];
            }
        }
        int ans = 0;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!grid[y][x]) continue;

                queue<coord> q;
                q.push({y, x});
                grid[y][x] = 0;

                while (!q.empty()) {
                    coord now = q.front();
                    q.pop();

                    for (int i = 0; i < 8; i++) {
                        int ny = now.y + diry[i];
                        int nx = now.x + dirx[i];
                        if (ny < 0 || nx < 0 || ny >= h || nx >= w) continue;
                        if (!grid[ny][nx]) continue;

                        grid[ny][nx] = 0;
                        q.push({ny, nx});
                    }
                }
                ans++;
            }
        }

        cout << ans << "\n";
    }
}