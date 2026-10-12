#include <iostream>
#include <algorithm>
using namespace std;



int main() {
    int n;
    cin >> n;

    int cost[1010][3];
    int dp[1010][3];

    for (int i = 0; i < n; i++) {
        cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
    }

    for (int i = 0; i < 3; i++) {
        dp[0][i] = cost[0][i];
    }

    // dp 점화식
    for (int i = 1; i < n; i++) {
        dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + cost[i][0];
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + cost[i][1];
        dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + cost[i][2];
    }

    cout << min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
}