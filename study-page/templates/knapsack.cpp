#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int capacity;
vector<pair<int, int>> items; // weight, value
vector<long long> dp;

long long knapsack() {
    dp.assign(capacity + 1, 0);
    for (const auto& [weight, value] : items) {
        for (int w = capacity; w >= weight; w--) {
            dp[w] = max(dp[w], dp[w - weight] + value);
        }
    }
    return dp[capacity];
}
