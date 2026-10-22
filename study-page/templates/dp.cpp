#include <vector>
using namespace std;
using ll = long long;

int N;
vector<ll> dp;

ll countWays() { // 0 <= N <= 90
    dp.assign(N + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= N; i++) {
        dp[i] = dp[i - 1];
        if (i >= 2) dp[i] += dp[i - 2];
    }
    return dp[N];
}
