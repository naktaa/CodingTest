// 0이면 못감
// 검은방을 최소한으로 바꿔서 (1,1) --> (N,N)
// 우선순위 큐에 넣으면서 바꾼 횟수를 최소로 잡고 진행
// visited 처리
// 맨해튼 거리도 따져봄

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct node {
    int y, x, cnt; // y, x, 바꾼 횟수
    int dist;      // 현재 지점에서 끝방까지의 맨해튼 거리
    bool operator<(node other) const {
        if (cnt != other.cnt) return cnt > other.cnt;
        return dist > other.dist;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<vector<int>> grid(N, vector<int>(N, 0));
    for (int r = 0; r < N; r++) {
        string rooms;
        cin >> rooms;
        int c = 0;
        for (const auto& room : rooms) {
            grid[r][c++] = room - '0';
        }
    }

    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};
    vector<vector<int>> visited(N, vector<int>(N, 0));
    priority_queue<node> pq;
    pq.push({0, 0, 0, 2 * (N - 1)});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        // 끝방 도착
        if (now.y == N - 1 && now.x == N - 1) {
            cout << now.cnt << "\n";
            break;
        }

        for (int i = 0; i < 4; i++) {
            int ny = now.y + diry[i];
            int nx = now.x + dirx[i];
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue; // grid 벗어나면 pass
            if (visited[ny][nx]) continue;                        // 방문했으면 pass


            visited[ny][nx] = 1;
            // 하얀 방
            if (grid[ny][nx]) {
                pq.push({ny, nx, now.cnt, now.dist - diry[i] - dirx[i]});
            }
            // 검은 방인 경우 바꾼 수 1 증가
            else {
                pq.push({ny, nx, now.cnt + 1, now.dist - diry[i] - dirx[i]});
            }
        }
    }
}