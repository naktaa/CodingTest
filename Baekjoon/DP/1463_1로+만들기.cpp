#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int N;
    vector<int> dp;
    cin >> N;
    dp.assign(N + 1, 1e8);

    queue<int> q;
    q.push(N);
    dp[N] = 0;

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        // cout << now << " ";

        if (now % 3 == 0) {
            int n1 = now / 3;
            if (dp[now] + 1 < dp[n1]) {
                dp[n1] = dp[now] + 1;
                q.push(n1);
            }
        }
        if (now % 2 == 0) {
            int n1 = now / 2;
            if (dp[now] + 1 < dp[n1]) {
                dp[n1] = dp[now] + 1;
                q.push(n1);
            }
        }

        if (now != 0) {
            if (dp[now] + 1 < dp[now - 1]) {
                dp[now - 1] = dp[now] + 1;
                q.push(now - 1);
            }
        }
    }

    cout << dp[1] << "\n";
}