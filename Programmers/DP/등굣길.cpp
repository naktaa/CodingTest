// n x m 그리드  |  1 < m,n < 100
// 오른쪽 아래쪽만 이동 --> 어딜 갈수있든 무조건 최소거리 보장
// (y, x)에 대해 위에서 내려오는 경우 + 왼쪽에서 오는 경우 해서 dp
// ----------------------------------------------------------------------------
// 각 계산마다 모듈러연산 적용해서 해줘도 동일한 답 나옴

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

int diry[] = {0, 1};
int dirx[] = {1, 0};

int solution(int m, int n, vector<vector<int>> puddles) {
    int grid[n][m]; // grid n x m -> 1인 지점 웅덩이
    int dp[n][m];   // path 개수 저장
    memset(grid, 0, sizeof(grid));
    memset(dp, 0, sizeof(dp));
    for (vector<int> puddle : puddles) {
        grid[puddle[1] - 1][puddle[0] - 1] = 1;
    }
    // 첫번째 줄 가능한 곳 모두 1로 만들고 시작
    for (int y = 0; y < n; y++) {
        if (grid[y][0] == 1) break;
        dp[y][0] = 1;
    }
    for (int x = 0; x < m; x++) {
        if (grid[0][x] == 1) break;
        dp[0][x] = 1;
    }

    // 한줄씩 더하기
    for (int y = 1; y < n; y++) {
        for (int x = 1; x < m; x++) {
            if (grid[y][x] == 1) continue; // 웅덩이일 경우 pass
            dp[y][x] = (dp[y - 1][x] + dp[y][x - 1]) % 1000000007;
        }
    }
    return dp[n - 1][m - 1];
}