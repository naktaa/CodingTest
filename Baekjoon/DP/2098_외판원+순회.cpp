#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int N;                 // 도시 개수
vector<vector<int>> W; // 이동 비용
int dp[1 << 16][16];   // 방문한 도시, 마지막 방문
int ans = 21e8;

int dfs(int visited, int last) {
    // 모든 도시 돌았을 때 시작 도시로 돌아오는 비용
    if (visited == ((1 << N) - 1)) {
        // 비용이 0일 때 최대로 return해서 빼버림
        if (W[last][0] == 0) return 21e8;
        return W[last][0];
    }

    int& cost = dp[visited][last];
    if (cost != -1) return cost;
    cost = 21e8;

    for (int i = 0; i < N; i++) {
        if ((visited & (1 << i)) != 0 || W[last][i] == 0) continue;
        int next_visited = visited | (1 << i);
        cost = min(cost, dfs(next_visited, i) + W[last][i]);
    }

    return cost;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    W.assign(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> W[i][j];
        }
    }

    memset(dp, -1, sizeof(dp));
    ans = min(ans, dfs(1 << 0, 0));

    cout << ans << "\n";
}