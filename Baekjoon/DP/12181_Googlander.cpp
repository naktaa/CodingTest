// R C 그리드
// 좌하단에서 위를 바라본채로 시작 --> (0,0)에서 오른쪽 바라본채로 시작
// 전진 or 우회전
// 2가지 행동을 할 수 없을때까지 진행
// 1-based
// -------------------------------------------------------------------
// 파스칼 삼각형의 법칙

#include <iostream>
#include <vector>
using namespace std;

vector<int> R; // 그리드 정보
vector<int> C;
long long grid[30][30];

int main() {
    // grid 초기값 설정
    for (int i = 1; i <= 25; i++) {
        grid[i][1] = 1;
        grid[1][i] = 1;
    }

    for (int r = 2; r <= 25; ++r) {
        for (int c = 2; c <= 25; ++c) {
            grid[r][c] = grid[r - 1][c] + grid[r][c - 1];
        }
    }

    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int r, c;
        cin >> r >> c;
        R.push_back(r);
        C.push_back(c);
    }
    for (int tc = 1; tc <= T; tc++) {
        cout << "Case #" << tc << ": " << grid[R[tc - 1]][C[tc - 1]] << "\n";
    }
}