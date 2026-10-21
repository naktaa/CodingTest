#include <algorithm>
#include <array>
#include <vector>
using namespace std;

vector<vector<int>> edges;
vector<long long> weight;
vector<array<long long, 2>> dp;

void dfs(int now, int prev) {
    dp[now][0] = 0;
    dp[now][1] = weight[now];
    for (int next : edges[now]) {
        if (next == prev) continue;
        dfs(next, now);
        dp[now][0] += max(dp[next][0], dp[next][1]);
        dp[now][1] += dp[next][0];
    }
}

long long independentSet(int root) {
    dp.assign(edges.size(), array<long long, 2>{0, 0});
    dfs(root, root);
    return max(dp[root][0], dp[root][1]);
}
