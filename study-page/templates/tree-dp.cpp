#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

vector<vector<int>> edges;
vector<int> weight;
vector<vector<ll>> dp;

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

ll independentSet(int root) {
    int len = edges.size();
    dp.assign(len, vector<ll>(2, 0));
    dfs(root, root);
    return max(dp[root][0], dp[root][1]);
}
