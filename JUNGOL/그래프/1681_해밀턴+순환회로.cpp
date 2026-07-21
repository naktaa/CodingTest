// 단방향 그래프
// 모든 장소 한번씩 방문하고 돌아오기
// 이동할수 없는 길은 0
// 비트마스킹 dp 2차원
// 일단 백트래킹으로

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 21e8;

int N; // 최대 13
vector<vector<int>> Cost;
vector<vector<int>> dp;
int sum = 0;

void dfs(int last, int visited) {
    if (visited == (1 << N) - 1) {
        return;
    }

    for (int i = 1; i < N; i++) {
        if (visited & (1 << i) || !Cost[last][i]) continue;
        int nextVisited = visited | (1 << i);
        if (dp[last][visited] + Cost[last][i] >= dp[i][nextVisited]) continue;
        dp[i][nextVisited] = dp[last][visited] + Cost[last][i];
        dfs(i, nextVisited);
    }
}

int main() {
    cin >> N;
    Cost.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int cost;
            cin >> cost;
            Cost[i][j] = cost;
        }
    }
    dp.assign(N, vector<int>(1 << N, INF));
    dp[0][1] = 0;
    dfs(0, 1 << 0);

    int ans = INF;
    for (int i = 1; i < N; i++) {
        if (!Cost[i][0]) continue;
        int minCost = dp[i][(1 << N) - 1] + Cost[i][0];
        ans = min(ans, minCost);
    }

    cout << ans;
}