/*
dp 문제
원형으로 이어져있음
N개 중에 인접하지 않게 K개 선택
dp -> 2차원으로 구성, dp[몇번째][개수]
첫번째를 선택하냐 안하냐
*/

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int N, K;
    cin >> N >> K;

    if (K > N / 2) {
        cout << 0;
        return;
    }

    vector<vector<ll>> dp(N, vector<ll>(K, -1));
    dp[0][1] = 1;
    dp[1][1] = 1;
    dp[2][2] = 1;
    for (int i = 3; i < N; i++) {
        for (int k = 1; k < K; k++) {
            dp[i][k] = dp[i - 2][k - 1] + dp[i - 3][k - 1];
        }
    }
}