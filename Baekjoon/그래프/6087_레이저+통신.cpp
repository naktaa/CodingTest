// W x H grid
// c를 연결하기 위해 필요한 거울 개수의 min
// 거울 /  \  에 닿으면 굴절
// 빈칸 .  벽 *   출발도착 c
// bfs하면서 회전한 횟수, 맨해튼 거리 기준으로 도착점까지 진행
// 우선순위큐 cnt가 적을수록 -> dist가 작을수록
// deque로 01 bfs 해보기 --> 안됨
// ------------------------------------------------------------------------------------
// 같은 지점에 더 적은 거울로 올 수 있음
// 단순하게 visited 0 1 X
// dir 추가해 3차원으로 만들어서 dp

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <cmath>
using namespace std;
using PR = pair<int, int>;
const int INF = 21e8;

struct node {
    int y, x, dir, cnt, dist;
    bool operator<(node other) const {
        if (cnt != other.cnt) return cnt > other.cnt;
        return dist > other.dist;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int W, H;
    vector<string> grid;
    vector<PR> C; // 출발 도착
    cin >> W >> H;

    for (int i = 0; i < H; i++) {
        string line;
        cin >> line;
        grid.push_back(line);
    }
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (grid[y][x] == 'C') C.push_back({y, x});
        }
    }

    vector<PR> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 상 하 좌 우 0 1 2 3
    vector<vector<vector<int>>> visited(H, vector<vector<int>>(W, vector<int>(4, INF)));
    // deque<node> q;
    priority_queue<node> pq;
    pq.push({C[0].first, C[0].second, -1, 0, abs(C[0].first - C[1].first) + abs(C[0].second - C[1].second)}); // 처음 시작 dir -1로 설정

    while (1) {
        node now = pq.top();
        pq.pop();
        // 다른 C에 도착하면 cnt 출력하고 종료
        if (now.y == C[1].first && now.x == C[1].second) {
            cout << now.cnt << "\n";
            break;
        }

        for (int i = 0; i < 4; i++) {
            int ny = now.y + dirs[i].first;
            int nx = now.x + dirs[i].second;

            if (ny < 0 || nx < 0 || ny >= H || nx >= W) continue; // grid 벗어나면 pass
            if (grid[ny][nx] == '*') continue;                    // 벽이면 pass

            // 제일 처음
            if (now.dir == -1) {
                visited[ny][nx][i] = now.cnt;
                pq.push({ny, nx, i, now.cnt, abs(now.y - ny) + abs(now.x - nx)});
                continue;
            }
            // 방향 같으면 cnt 증가 x
            if (now.dir == i) {
                if (now.cnt >= visited[ny][nx][i]) continue;
                visited[ny][nx][i] = now.cnt;
                pq.push({ny, nx, i, now.cnt, abs(now.y - ny) + abs(now.x - nx)});
            }
            // 방향 달라지면 cnt++
            else {
                if (now.cnt + 1 >= visited[ny][nx][i]) continue;
                visited[ny][nx][i] = now.cnt + 1;
                pq.push({ny, nx, i, now.cnt + 1, abs(now.y - ny) + abs(now.x - nx)});
            }
        }
    }
}