// 모든 경우의 수 조합해서 돌려보기
// permutation 사용해보기

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct coord {
    int y, x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<int>> grid;     // N x M
    vector<vector<int>> grid_cpy; // grid 복사본
    vector<coord> Empty;          // 벽 세울 후보 좌표
    vector<coord> virus;          // 바이러스 좌표
    vector<int> choose;           // 어떤 좌표 선택할지 permutation용
    int safe = 0;
    int ans = -1;
    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};

    cin >> N >> M;
    grid.resize(N, vector<int>(M));
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            cin >> grid[r][c];

            if (grid[r][c] == 0) {
                Empty.push_back({r, c});
                safe++;
            }
            else if (grid[r][c] == 2) {
                virus.push_back({r, c});
                safe++;
            }
        }
    }
    choose.assign(Empty.size(), 0);
    for (int i = 0; i < 3; i++) {
        choose[i] = 1;
        safe--;
    }

    // 모든 경우의 수 bfs
    do {
        int safe_cpy = safe; // ans 비교용
        grid_cpy = grid;
        for (int i = 0; i < choose.size(); i++) {
            if (!choose[i]) continue;
            grid_cpy[Empty[i].y][Empty[i].x] = 1;
        }
        queue<coord> q;
        for (const auto& v : virus) {
            q.push({v.y, v.x});
        }

        while (!q.empty()) {
            coord now = q.front();
            q.pop();
            safe_cpy--;

            for (int i = 0; i < 4; i++) {
                int ny = now.y + diry[i];
                int nx = now.x + dirx[i];

                if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
                if (grid_cpy[ny][nx]) continue;
                grid_cpy[ny][nx] = 2;
                q.push({ny, nx});
            }
        }

        ans = max(ans, safe_cpy);
    } while (prev_permutation(choose.begin(), choose.end()));

    cout << ans << "\n";
}