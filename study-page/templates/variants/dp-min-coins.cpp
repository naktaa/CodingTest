#include <algorithm>
#include <vector>
using namespace std;

const int INF = 1000000000;
int N;
vector<int> nums, dp;

int minCoins() {
    dp.assign(N + 1, INF);
    dp[0] = 0;
    for (int now = 1; now <= N; now++) {
        for (int next : nums) {
            if (next > now) continue;
            if (dp[now - next] == INF) continue;
            dp[now] = min(dp[now], dp[now - next] + 1);
        }
    }
    if (dp[N] == INF) return -1;
    return dp[N];
}
