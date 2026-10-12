// 1-based
// (1,1) --> (N,M) 으로 가기 위해 부숴야 하는 벽의 최소 개수
// 0은 빈방, 1이면 벽
// 빈방만 이동 가능, 벽 부수고 가능
// dp? 또는 다익스트라
// 다익스트라로 y,x,cnt 해서 cnt 적은 곳으로 없으면 하나 부시기
// cnt 작은 순으로 계속 탐색하면서 (N,M) 도착하면 return 하고 끝
// ------------------------------------------------------------------------------------
// 다른 방법으로 0-1 BFS 가능 --> deque 이용
// 0이면 deque의 앞에, 1이면 deque의 뒤에 넣으면서 front 탐색하여 최소비용으로 진행

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct coord {
    int y, x, cnt; // y, x, 벽 부순 횟수
    bool operator<(coord other) const {
        return cnt > other.cnt;
    }
};
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};

int find(int N, int M, const vector<vector<int>>& mage) {
    vector<vector<int>> visited(N + 1, vector<int>(M + 1));
    for (auto& v : visited) {
        fill(v.begin(), v.end(), -1);
    }
    priority_queue<coord> pq;
    pq.push({1, 1, 0});
    visited[1][1] = 0;

    while (!pq.empty()) {
        coord now = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++) {
            int ny = now.y + diry[i];
            int nx = now.x + dirx[i];
            if (ny < 1 || nx < 1 || ny > N || nx > M) continue;
            if (visited[ny][nx] != -1) continue;

            visited[ny][nx] = now.cnt + mage[ny][nx];
            pq.push({ny, nx, now.cnt + mage[ny][nx]});
        }
    }

    return visited[N][M];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N;                 // 가로, 세로  1 < N,M < 100
    vector<vector<int>> mage; // 미로 정보
    cin >> M >> N;
    mage.assign(N + 1, vector<int>(M + 1));
    for (int r = 1; r <= N; r++) {
        string temp;
        cin >> temp;
        int col = 1;
        for (char c : temp) {
            mage[r][col++] = c - '0';
        }
    }

    cout << find(N, M, mage) << "\n";

    return 0;
}

// for (vector<int> a : mage) {
//     for (int s : a) {
//         cout << s << " ";
//     }
//     cout << "\n";
// }


// cout << "\n";
// cout << "----------------------";
// cout << "\n";


// cout << "(" << now.y << " " << now.x << "): " << now.cnt << "\n";