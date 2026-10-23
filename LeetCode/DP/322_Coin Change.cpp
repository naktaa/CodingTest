#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1e4 + 1;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INF);
        dp[0] = 0;

        for (const int& coin : coins) {
            for (int i = 0; i < amount; i++) {
                if (i + coin > amount) break;
                if (dp[i] == INF) continue;
                dp[i + coin] = min(dp[i + coin], dp[i] + 1);
            }
        }

        return (dp[amount] == INF ? -1 : dp[amount]);
    }
};