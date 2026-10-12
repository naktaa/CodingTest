// 큐 2개로 관리
// 플러드필 하면서 지훈이 큐가 비게 되면 impossible
// 지훈 --> fire 순서
// 미로의 외곽에 도착하면 탈출시간 출력
// ========================================================================
// size만큼 queue 돌려주기 --> 같은 시간대 다 돌려줘야됨

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct node {
    int y, x, time = 0; // 좌표, 탈출시간
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int R, C;            // R x C
    vector<string> miro; // 미로
    node J;              // 지훈이 초기위치
    vector<node> F;      // 불 초기위치
    int diry[] = {0, 1, 0, -1};
    int dirx[] = {1, 0, -1, 0};

    cin >> R >> C;
    miro.resize(R);
    for (int r = 0; r < R; r++) {
        cin >> miro[r];
        for (int c = 0; c < C; c++) {
            if (miro[r][c] == 'J')
                J = {r, c};
            else if (miro[r][c] == 'F')
                F.push_back({r, c});
        }
    }

    queue<node> jihun;
    queue<node> fire;
    jihun.push(J);
    for (const auto& f : F) {
        fire.push(f);
    }

    while (!jihun.empty()) {
        // 불 시작
        int size = fire.size();
        while (size--) {
            node now = fire.front();
            fire.pop();

            for (int i = 0; i < 4; i++) {
                int ny = now.y + diry[i];
                int nx = now.x + dirx[i];

                if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
                if (miro[ny][nx] == '#' || miro[ny][nx] == 'J' || miro[ny][nx] == 'F') continue;

                miro[ny][nx] = 'F';
                fire.push({ny, nx});
            }
        }

        size = jihun.size();
        while (size--) {
            node now = jihun.front();
            jihun.pop();
            // 외곽에 위치하면 종료
            if (now.y == 0 || now.x == 0 || now.y == R - 1 || now.x == C - 1) {
                cout << now.time + 1 << "\n";
                return 0;
            }

            for (int i = 0; i < 4; i++) {
                int ny = now.y + diry[i];
                int nx = now.x + dirx[i];

                if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
                if (miro[ny][nx] == '#' || miro[ny][nx] == 'J' || miro[ny][nx] == 'F') continue;

                miro[ny][nx] = 'J';
                jihun.push({ny, nx, now.time + 1});
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}