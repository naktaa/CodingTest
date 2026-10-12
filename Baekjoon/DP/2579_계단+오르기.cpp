#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<int> stairs;
    vector<vector<int>> dp;

    cin >> N;
    stairs.resize(N);
    dp.resize(N, vector<int>(2, 0));
    for (int i = 0; i < N; i++) {
        cin >> stairs[i];
    }

    dp[0][0] = stairs[0];
    if (N >= 2) {
        dp[1][0] = stairs[1];
        dp[1][1] = dp[0][0] + stairs[1];

        for (int i = 2; i < N; i++) {
            dp[i][0] = max(dp[i - 2][0], dp[i - 2][1]) + stairs[i];
            dp[i][1] = dp[i - 1][0] + stairs[i];
        }
    }


    cout << max(dp[N - 1][0], dp[N - 1][1]) << "\n";
}