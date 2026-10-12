// 이어진 집마다 단지로 묶기
// 집의 수 오름차순으로 출력
// visited 주의해서 넣기
// --------------------------------
// 이런 경로 문제에서 dfs 사용하는거 고려해보기 메모리 더 적음

#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main() {
    int N;                    // 5 < N < 25
    vector<vector<int>> grid; // N x N 지도
    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};

    cin >> N;
    grid.resize(N, vector<int>(N, 0));
    for (int r = 0; r < N; r++) {
        string row;
        cin >> row;
        int index = 0;
        for (int c = 0; c < N; c++) {
            grid[r][c] = row[index++] - '0';
        }
    }

    // bfs 시작
    vector<vector<int>> visited(N, vector<int>(N, 0));    // 방문여부
    priority_queue<int, vector<int>, greater<int>> danji; // 오름차순으로 집의 수 정렬

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (grid[r][c] == 0 || visited[r][c] == 1) continue; // 집이 없거나 방문했으면 pass
            queue<pair<int, int>> q;
            int cnt = 0;
            q.push({r, c});
            visited[r][c] = 1;

            while (!q.empty()) {
                auto now = q.front();
                q.pop();
                cnt++; // 단지 수 하나씩 증가

                for (int i = 0; i < 4; i++) {
                    int ny = now.first + diry[i];
                    int nx = now.second + dirx[i];
                    if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // 지도 벗어나면 pass
                    if (grid[ny][nx] == 0 || visited[ny][nx] == 1) continue;

                    visited[ny][nx] = 1;
                    q.push({ny, nx});
                }
            }
            danji.push(cnt);
        }
    }

    cout << danji.size() << "\n"; // 총 단지수 출력
    while (!danji.empty()) {
        int ans = danji.top();
        danji.pop();
        cout << ans << "\n"; // 집의 수 출력
    }
}