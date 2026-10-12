// 배양액 땅 = R+G개 이상에 10개 이하
// 위치 미리 구해놓고 경우의 수 다 돌려가면서 MAX 구하기
// 0: 호수  |  1: 그냥 땅  |  2: 배양액 가능 땅
// 4: 초록색 땅  |  5: 빨간색 땅  |  6: 꽃
// 동일한 시간에 도달해야지 꽃 피우기 가능
// 플러드필 하고 땅 0으로 만들기
// ===========================================================================
// 백트래킹 조건에서 아무것도 안넣고 진행하는것도 추가
// now 뽑을 때 꽃으로 변했으면 플러드필 안하고 pass

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

struct coord {
    int y, x;
};
struct info {
    int state, time;
};
struct node {
    int y, x, state, time;
};

int N, M, G, R;
vector<vector<info>> grid; // N x M
vector<vector<info>> cpy;  // grid 복사본
vector<coord> grow;        // 배양액 뿌릴 수 있는 좌표
vector<int> used;          // 배양액 뿌렸는지
int cntG = 0, cntR = 0;    // G, R 사용한 횟수
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};
int ans = -1;

void bfs() {
    // cout << "\n===============================================\n";

    cpy = grid;
    int cnt = 0; // 꽃 개수
    queue<node> q;
    for (int i = 0; i < used.size(); i++) {
        if (used[i] != 4 && used[i] != 5) continue; // G, R만 queue에 넣기
        q.push({grow[i].y, grow[i].x, used[i], 0});
        cpy[grow[i].y][grow[i].x] = {used[i], 0}; // 배양액 종류 넣어주기
    }

    while (!q.empty()) {
        node now = q.front();
        q.pop();
        if (cpy[now.y][now.x].state == 6) continue; // 꽃으로 변했으면 pass
        // cout << "(" << now.y << ", " << now.x << ") --> state = " << now.state << ", time = " << now.time << "\n";

        for (int i = 0; i < 4; i++) {
            int ny = now.y + diry[i];
            int nx = now.x + dirx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
            if (cpy[ny][nx].state == 0 || cpy[ny][nx].state == 6) continue; // 호수거나 꽃이면 pass
            if (now.state == cpy[ny][nx].state) continue;                   // 이미 퍼졌으면 pass

            // 다른 색 만나면 꽃 만들기
            if (abs(now.state - cpy[ny][nx].state) == 1) {
                if (now.time + 1 == cpy[ny][nx].time) {
                    cpy[ny][nx].state = 6;
                    cnt++;
                }
                continue;
            }
            cpy[ny][nx] = {now.state, now.time + 1};
            q.push({ny, nx, now.state, now.time + 1});
        }
    }

    ans = max(ans, cnt);
}

void func(int level) {
    if (level == grow.size()) {
        if (cntG == G && cntR == R) {
            bfs();
        }
        return;
    }

    if (cntG < G) {
        cntG++;
        used[level] = 4;
        func(level + 1);
        cntG--;
        used[level] = 2;
    }

    if (cntR < R) {
        cntR++;
        used[level] = 5;
        func(level + 1);
        cntR--;
        used[level] = 2;
    }

    func(level + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M >> G >> R;

    grid.resize(N, vector<info>(M));
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            cin >> grid[y][x].state;
            if (grid[y][x].state == 2) grow.push_back({y, x});
        }
    }
    used.resize(grow.size(), 2);

    func(0);

    cout << ans << "\n";
}