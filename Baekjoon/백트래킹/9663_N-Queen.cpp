// N x N 체스판에서 가로, 세로, 대각선 안 겹치게 N개 놓기
// 단순하게 백트래킹하기
// 가로 세로 대각 같이 따지기?
// 행으로 내려가면서 세로 대각선 2가지 경우만 따지기
// visited를 세로, 왼대각선, 오대각선 3개 만들어서 판별
// 0 0 1 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 0 0 0 0 0
// 13 부터 오래 걸리면서 14 15 시간초과
// 탐색하지 말고 visited로 관리

#include <iostream>
#include <vector>
using namespace std;

int N;
int ans;
vector<vector<int>> grid; // N x N 체스판
vector<int> visited_col, visited_diaL, visited_diaR;
/*
int diry[] = {-1, 1};
int diay[] = {1, 1, -1, -1};
int diax[] = {1, -1, -1, 1};
int ny, nx;     // 다음 위치
int flag_queen; // 퀸 둘 수 있는지 없는지 여부
*/

void queen(int level) {
    if (level >= N) {
        ans++;
        return;
    }
    for (int x = 0; x < N; x++) {
        if (visited_col[x] > 0 || visited_diaL[level - x + N] > 0 || visited_diaR[level + x] > 0) continue;

        visited_col[x]++;
        visited_diaL[level - x + N]++;
        visited_diaR[level + x]++;

        queen(level + 1);

        visited_col[x]--;
        visited_diaL[level - x + N]--;
        visited_diaR[level + x]--;

        /*
        flag_queen = 1;

        // 같은 열
        for (int i = 0; i < 2; i++) {
            ny = level, nx = x;
            while (1) {
                ny += diry[i];

                if (ny < 0 || ny >= N) break; // 그리드 벗어나면 pass
                if (grid[ny][x]) {
                    flag_queen = 0;
                    break;
                }
            }
            if (!flag_queen) break;
        }
        if (!flag_queen) continue;

        // 대각선
        for (int i = 0; i < 4; i++) {
            ny = level, nx = x;
            while (1) {
                ny += diay[i];
                nx += diax[i];

                if (ny < 0 || nx < 0 || ny >= N || nx >= N) break;
                if (grid[ny][nx]) {
                    flag_queen = 0;
                    break;
                }
            }
            if (!flag_queen) break;
        }

        if (flag_queen) {
            grid[level][x] = 1;
            queen(level + 1);
            grid[level][x] = 0;
        }
        */
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    grid.assign(N, vector<int>(N, 0));
    visited_col.assign(N, 0);
    visited_diaL.assign(2 * N + 1, 0);
    visited_diaR.assign(2 * N + 1, 0);

    queen(0);
    cout << ans << "\n";
}