// 3x3을 1줄 string 으로 관리 '103425786'
// (0,0) - (2,2) mod 3 으로 좌표
// 각 방문 상태를 set으로 관리
// queue에 넣으면서 bfs하면서 min값 찾기
// 이동 방향은 / & 4방향으로 설정해서 찾기 좌표와 유사

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
using namespace std;

struct node {
    string state; // 상태
    int cnt;      // 방문 횟수
};
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};

int main() {
    string init = "";              // 처음 상태
    unordered_set<string> visited; // 방문 여부
    for (int i = 0; i < 9; i++) {
        char n;
        cin >> n;
        init += n;
    }
    if (init == "123456780") {
        cout << 0 << "\n";
        return 0;
    }

    // queue 에다 상태 넣으면서 중복 관리
    queue<node> q;
    q.push({init, 0});
    visited.insert(init);

    // queue 시작
    while (!q.empty()) {
        node now = q.front();
        q.pop();

        int index = 0; // 0 위치 찾기
        for (char c : now.state) {
            if (c == '0') break;
            index++;
        }
        int y = index / 3;
        int x = index % 3;

        // 빈 공간 가능한 곳들로 이동
        for (int i = 0; i < 4; i++) {
            int ny = y + diry[i];
            int nx = x + dirx[i];
            if (ny < 0 || nx < 0 || ny > 2 || nx > 2) continue;

            string next = now.state;
            int swap_index = ny * 3 + nx;
            char temp = now.state[swap_index];
            next[index] = temp;
            next[swap_index] = '0';
            // 목표 상태에 도달하면 출력하고 end
            if (next == "123456780") {
                cout << now.cnt + 1 << "\n";
                return 0;
            }
            if (visited.find(next) != visited.end()) continue; // set에 존재하면 pass
            visited.insert(next);
            q.push({next, now.cnt + 1});
        }
    }

    cout << -1 << "\n";
}