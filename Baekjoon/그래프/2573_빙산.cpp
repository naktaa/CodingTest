// 먼저 녹이고 bfs하면서 2덩어리 이상인지 확인

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct node {
    int y, x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<int>> grid;
    vector<vector<int>> temp;
    int cnt = 0; // 빙판 남은 개수
    int ans = 0; // 몇년

    cin >> N >> M;
    grid.resize(N, vector<int>(M, 0));
    temp.resize(N, vector<int>(M, 0));
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            cin >> grid[y][x];
            if (grid[y][x]) cnt++;
        }
    }

    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};

    while (1) {
        // 빙판 개수가 0개 될 때까지 한 덩어리였으면 0 출력하고 종료
        if (cnt == 0) {
            cout << 0 << "\n";
            break;
        }

        ans++;
        // 녹이기
        temp = grid;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (!grid[y][x]) continue; // 0 이면 pass
                int zero = 0;              // 0과 접한 지점의 수

                for (int i = 0; i < 4; i++) {
                    int ny = y + diry[i];
                    int nx = x + dirx[i];

                    if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue; // grid 벗어나면 pass
                    if (grid[ny][nx]) continue;                           // 0 아니면 pass
                    zero++;
                }

                temp[y][x] -= zero;
                if (temp[y][x] <= 0) {
                    cnt--;
                    temp[y][x] = 0;
                }
            }
        }
        grid = temp;
        // cout << "\n";
        // for (int y = 0; y < N; y++) {
        //     for (int x = 0; x < M; x++) {
        //         cout << grid[y][x] << " ";
        //     }
        //     cout << "\n";
        // }

        // 플러드필
        queue<node> q;
        int seperated_flag = 0; // 분리 됐는지 flag

        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (!temp[y][x]) continue; // 0 이면 pass
                q.push({y, x});

                // flag가 1이면 2 덩어리로 분리되었으니 출력하고 종료
                if (seperated_flag) {
                    cout << ans << "\n";
                    return 0;
                }

                while (!q.empty()) {
                    node now = q.front();
                    q.pop();

                    for (int i = 0; i < 4; i++) {
                        int ny = now.y + diry[i];
                        int nx = now.x + dirx[i];

                        if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue; // grid 벗어나면 pass
                        if (!temp[ny][nx]) continue;                          // 0 아니면 pass

                        temp[ny][nx] = 0;
                        q.push({ny, nx});
                    }
                }
                seperated_flag = 1;
            }
        }
    }
}