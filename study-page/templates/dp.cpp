#include <vector>
using namespace std;

int n;
vector<long long> dp;

long long countWays() { // 0 <= n <= 90
    dp.assign(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (i >= 2) dp[i] += dp[i - 2];
    }
    return dp[n];
}
