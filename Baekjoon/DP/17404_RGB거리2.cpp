/*
연속될 때 다른 색
1번 N번 색이 달라야함
3차원?
=================================================================
선형문제로 가능
첫 집을 고정해서 3번 돌리고 마지막 dp값이 고정한 색과 다른것만 비교
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<vector<int>> house;
    int ans = 1e8;

    cin >> N;
    house.resize(N, vector<int>(3, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> house[i][j];
        }
    }

    for (int start = 0; start < 3; start++) {
        vector<vector<int>> dp(N, vector<int>(3, 1e8));
        dp[0][start] = house[0][start];

        for (int j = 1; j < N; j++) {
            dp[j][0] = min(dp[j - 1][1], dp[j - 1][2]) + house[j][0];
            dp[j][1] = min(dp[j - 1][0], dp[j - 1][2]) + house[j][1];
            dp[j][2] = min(dp[j - 1][0], dp[j - 1][1]) + house[j][2];
        }

        for (int last = 0; last < 3; last++) {
            if (start == last) continue; // 1번 N번 같은 경우는 제외
            ans = min(ans, dp[N - 1][last]);
        }
    }

    cout << ans << "\n";
}