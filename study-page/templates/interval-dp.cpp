#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

const ll INF = 1'000'000'000'000'000'000LL;
vector<int> nums;
vector<ll> prefix;
vector<vector<ll>> dp;

ll mergeCost() {
    int len = nums.size();
    if (len == 0) return 0;
    prefix.assign(len + 1, 0);
    for (int i = 0; i < len; i++) prefix[i + 1] = prefix[i] + nums[i];
    dp.assign(len, vector<ll>(len, 0));
    for (int width = 2; width <= len; width++) {
        for (int left = 0; left + width <= len; left++) {
            int right = left + width - 1;
            dp[left][right] = INF;
            for (int k = left; k < right; k++) {
                ll next = dp[left][k] + dp[k + 1][right];
                next += prefix[right + 1] - prefix[left];
                dp[left][right] = min(dp[left][right], next);
            }
        }
    }
    return dp[0][len - 1];
}
