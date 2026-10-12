// 3차원 grid
// 방향 순서 -> 동서남북상하

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct coord {
    int l, r, c, time; // 좌표정보, 걸린 시간
};
int L, R, C;                     // 높이, 행, 열
vector<vector<string>> building; // 빌딩
coord start;                     // 시작 지점
int start_flag;                  // 시작 지점 찾았는지 flag
int escape_flag;                 // 탈출 flag
int dirl[] = {0, 0, 0, 0, -1, 1};
int dirr[] = {0, 0, 1, -1, 0, 0};
int dirc[] = {1, -1, 0, 0, 0, 0};

void floodfill() {
    queue<coord> q;
    q.push(start);
    building[start.l][start.r][start.c] = '#';

    while (!q.empty()) {
        coord now = q.front();
        q.pop();

        for (int i = 0; i < 6; i++) {
            int nl = now.l + dirl[i];
            int nr = now.r + dirr[i];
            int nc = now.c + dirc[i];

            if (nl < 0 || nr < 0 || nc < 0 || nl >= L || nr >= R || nc >= C) continue; // grid 벗어나면 pass
            if (building[nl][nr][nc] == '#') continue;                                 // 벽이면 pass
            if (building[nl][nr][nc] == 'E') {
                cout << "Escaped in " << now.time + 1 << " minute(s).\n";
                escape_flag = 1;
                return;
            }

            building[nl][nr][nc] = '#';
            q.push({nl, nr, nc, now.time + 1});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (1) {
        cin >> L >> R >> C;
        if (L == 0) return 0;

        // 초기화
        start_flag = 0, escape_flag = 0;
        building.assign(L, vector<string>(R));
        for (int l = 0; l < L; l++) {
            for (int r = 0; r < R; r++) {
                cin >> building[l][r];
                if (start_flag) continue;

                for (int c = 0; c < C; c++) {
                    if (building[l][r][c] != 'S') continue;
                    start = {l, r, c, 0};
                    start_flag = 1;
                }
            }
        }

        floodfill();
        if (!escape_flag) cout << "Trapped!\n";
    }
}