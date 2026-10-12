#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using pr = pair<int, int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<int> indegree;    // 진입차수
    vector<vector<pr>> need; // 필요 부품 관계
    vector<vector<int>> dp;

    cin >> N >> M;
    indegree.resize(N + 1, 0);
    need.resize(N + 1);
    dp.resize(N + 1, vector<int>(N + 1, 0));
    while (M--) {
        int X, Y, K; // X 를 만드는데 Y 가 K개 필요
        cin >> X >> Y >> K;
        indegree[X]++;
        need[Y].push_back({X, K});
    }

    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0) { // 기본 부품
            dp[i][i] = 1;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (const auto& next : need[now]) {
            for (int i = 1; i <= N; i++) {
                if (!dp[now][i]) continue;
                dp[next.first][i] += dp[now][i] * next.second;
            }

            indegree[next.first]--;
            if (indegree[next.first] == 0) q.push(next.first);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (dp[N][i] > 0) {
            cout << i << " " << dp[N][i] << "\n";
        }
    }
}
