#include <algorithm>
#include <limits>
#include <vector>
using namespace std;

vector<vector<int>> cost;
vector<long long> dp;

long long minAssignment() { // 정방 행렬, n <= 20
    int n = cost.size();
    int total = 1 << n;
    long long inf = numeric_limits<long long>::max() / 4;
    dp.assign(total, inf);
    dp[0] = 0;
    for (int mask = 0; mask < total; mask++) {
        if (dp[mask] == inf) continue;
        int person = __builtin_popcount(static_cast<unsigned>(mask));
        if (person == n) continue;
        for (int next = 0; next < n; next++) {
            if (mask & (1 << next)) continue;
            int nextMask = mask | (1 << next);
            dp[nextMask] = min(dp[nextMask], dp[mask] + cost[person][next]);
        }
    }
    return dp[total - 1];
}
