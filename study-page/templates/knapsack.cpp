#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int capacity;
vector<pair<int, int>> items; // weight, value
vector<ll> dp;

ll knapsack() {
    dp.assign(capacity + 1, 0);
    for (const auto& now : items) {
        int weight = now.first;
        int value = now.second;
        for (int w = capacity; w >= weight; w--) {
            dp[w] = max(dp[w], dp[w - weight] + value);
        }
    }
    return dp[capacity];
}
