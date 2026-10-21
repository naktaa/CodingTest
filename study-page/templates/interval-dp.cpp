#include <algorithm>
#include <limits>
#include <vector>
using namespace std;

vector<int> arr;
vector<long long> prefix;
vector<vector<long long>> dp;

long long mergeCost() {
    int n = arr.size();
    if (n == 0) return 0;
    prefix.assign(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + arr[i];
    dp.assign(n, vector<long long>(n, 0));
    for (int len = 2; len <= n; len++) {
        for (int left = 0; left + len <= n; left++) {
            int right = left + len - 1;
            dp[left][right] = numeric_limits<long long>::max() / 4;
            for (int k = left; k < right; k++) {
                long long next = dp[left][k] + dp[k + 1][right];
                next += prefix[right + 1] - prefix[left];
                dp[left][right] = min(dp[left][right], next);
            }
        }
    }
    return dp[0][n - 1];
}
