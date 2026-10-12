// 그리디하게 가성비 좋은 순서대로?
// =============================================================================
// 그리디 불가능 dp로 풀어야 됨
// 배낭 문제 종류
// i를 1씩 증가시켜 가면서 진행
// while문에서 초기화 부분과 if문 불필요
/*
while (N--) {
    int cost, client;
    cin >> cost >> client;

    for (int i = client; i <= C + client; i++) {
        dp[i] = min(dp[i], dp[i - client] + cost);
    }
}
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int C, N; // 고객, 도시
    vector<int> dp;
    int ans = 1e8;

    cin >> C >> N;
    dp.resize(C + 101, 1e8);
    dp[0] = 0;
    while (N--) {
        int cost, client;
        cin >> cost >> client;

        dp[client] = min(dp[client], cost);
        for (int i = client; i <= C + client; i++) {
            if (dp[i - client] == 1e8) continue;
            dp[i] = min(dp[i], dp[i - client] + cost);
        }
    }

    for (int i = C; i <= C + 100; i++) {
        ans = min(ans, dp[i]);
    }
    cout << ans << "\n";
}