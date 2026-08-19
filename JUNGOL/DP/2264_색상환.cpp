/*
dp 문제
원형으로 이어져있음
N개 중에 인접하지 않게 K개 선택
dp -> 2차원으로 구성, dp[몇번째][개수]
첫번째를 선택하냐 안하냐
몇번째마다 선택할지 정하면서 K개만큼 순회
===============================================
dp방식 개선 필요 -> dp[i][k] = 앞에서부터 i개의 색 중 k개를 선택한 경우의 수
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
        return 0;
    }

    vector<vector<ll>> dp1(N, vector<ll>(K + 1, 0));
    vector<vector<ll>> dp2(N, vector<ll>(K + 1, 0));
    // 첫번째 선택한 경우
    dp1[0][1] = 1;
    dp1[1][1] = 1;
    for (int i = 2; i < N - 1; i++) {
        for (int k = 1; k <= K; k++) {
            dp1[i][k] = (dp1[i - 1][k] + dp1[i - 2][k - 1]) % 1000000003;
        }
    }

    // 첫번째 선택 안한 경우
    for (int i = 0; i < N; i++) {
        dp2[i][0] = 1;
    }
    dp2[1][1] = 1;
    for (int i = 2; i < N; i++) {
        for (int k = 1; k <= K; k++) {
            dp2[i][k] = (dp2[i - 1][k] + dp2[i - 2][k - 1]) % 1000000003;
        }
    }

    int ans = (dp1[N - 2][K] + dp2[N - 1][K]) % 1000000003;
    cout << ans << "\n";
}