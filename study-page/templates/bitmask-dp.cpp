#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

const ll INF = 1'000'000'000'000'000'000LL;
vector<vector<int>> cost; // N <= 20, 비용의 절댓값 <= 10^9
vector<ll> dp;

int countBits(int mask) {
    int cnt = 0;
    while (mask > 0) {
        cnt += mask & 1;
        mask >>= 1;
    }
    return cnt;
}

ll minAssignment() {
    int len = cost.size();
    int total = 1 << len;
    dp.assign(total, INF);
    dp[0] = 0;
    for (int mask = 0; mask < total; mask++) {
        if (dp[mask] == INF) continue;
        int person = countBits(mask);
        if (person == len) continue;
        for (int next = 0; next < len; next++) {
            if (mask & (1 << next)) continue;
            int nextMask = mask | (1 << next);
            dp[nextMask] = min(dp[nextMask], dp[mask] + cost[person][next]);
        }
    }
    return dp[total - 1];
}
