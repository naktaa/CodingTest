// R x C 배열  R,C < 750
// 45도로 이어진 다이아몬드
/*
    1
   101
  10001
   101
    1
*/

#include <iostream>
#include <vector>
using namespace std;

int R, C;                    // R x C
vector<vector<int>> diamond; // 다이아몬드 그리드
int visited[750][750];       // 탐색했는지 여부
int ans;                     // 최대 크기
int diry[] = {-1, 1, 1, -1};
int dirx[] = {1, 1, -1, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> R >> C;
    diamond.assign(R, vector<int>(C));
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            cin >> diamond[r][c];
        }
    }

    // (0,0) 부터 탐색 시작
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (diamond[r][c] == 0) continue;
        }
    }
}