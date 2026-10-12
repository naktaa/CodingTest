// 2행 n열
// 50 70 x x x x x x x x x
// 40 90 x x x x x x x x x
// 점수 얻으면 인접한 스티커는 X
// 이전 열의 다른 행 vs 전전 열의 다른 행

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int n;
        vector<vector<int>> score; // 스티커 점수
        vector<vector<int>> dp;    // dp 테이블
        int ans;

        cin >> n;
        score.resize(2, vector<int>(n));
        dp.resize(2, vector<int>(n, -1));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                cin >> score[i][j];
                if (j == 0) dp[i][j] = score[i][j]; // dp 초기값 설정
            }
        }

        if (n == 1) {
            ans = max(dp[0][0], dp[1][0]);
        }
        else {
            dp[0][1] = dp[1][0] + score[0][1];
            dp[1][1] = dp[0][0] + score[1][1];
            if (n == 2) {
                ans = max(dp[0][1], dp[1][1]);
            }
            else {
                // 3번째 열부터 시작
                for (int c = 2; c < n; c++) {
                    for (int r = 0; r < 2; r++) {
                        dp[r][c] = max(dp[1 - r][c - 1], dp[1 - r][c - 2]) + score[r][c];
                    }
                }
                ans = max(dp[0][n - 1], dp[1][n - 1]);
            }
        }

        cout << ans << "\n";
    }
}