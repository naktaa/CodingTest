// 왼쪽, 오른쪽, 아래쪽으로만 이동
// 한번 간 곳은 안감
// (1,1) --> (N, M) 최대 구하기
// visited 좌표마다 만들면 안됨
// 아래로만 가기 때문에 한 줄마다 dp 계산하면 가능

#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int N, M;
vector<vector<int>> grid;   // N x M 지형
int dp[1001][1001];         // 가치 최대값 DP
int dx[] = {-1, 1};         // 왼쪽, 오른쪽
int LtoR[1001], RtoL[1001]; // 행마다 왼쪽 오른쪽 경로 계산

int main() {
    cin >> N >> M;
    grid.resize(N + 1, vector<int>(M + 1));
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= M; x++) {
            cin >> grid[y][x];
        }
    }

    dp[1][1] = grid[1][1];
    for (int x = 2; x <= M; x++) {
        dp[1][x] += dp[1][x - 1] + grid[1][x];
    }

    for (int y = 2; y <= N; y++) {
        // 위에서, 왼쪽에서
        LtoR[1] = dp[y - 1][1] + grid[y][1];
        for (int x = 2; x <= M; x++) {
            LtoR[x] = max(dp[y - 1][x], LtoR[x - 1]) + grid[y][x];
        }
        // 위에서, 오른쪽에서
        RtoL[M] = dp[y - 1][M] + grid[y][M];
        for (int x = M - 1; x >= 1; x--) {
            RtoL[x] = max(dp[y - 1][x], RtoL[x + 1]) + grid[y][x];
        }
        // LtoR, RtoL 중 큰 값으로 갱신
        for (int x = 1; x <= M; x++) {
            dp[y][x] = max(LtoR[x], RtoL[x]);
        }
    }

    cout << dp[N][M];
}