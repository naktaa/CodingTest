#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<int> indegree;
    vector<vector<int>> alias;
    vector<int> ans;

    cin >> N >> M;
    indegree.resize(N + 1, 0);
    alias.resize(N + 1);
    while (M--) {
        int cnt;
        cin >> cnt;
        vector<int> order;

        for (int i = 0; i < cnt; i++) {
            int n;
            cin >> n;
            order.push_back(n);
        }
        for (int i = 0; i < cnt - 1; i++) {
            alias[order[i]].push_back(order[i + 1]);
            indegree[order[i + 1]]++;
        }
    }

    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (indegree[i]) continue;
        q.push(i);
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        ans.push_back(now);

        for (const auto& next : alias[now]) {
            indegree[next]--;
            if (indegree[next]) continue;
            q.push(next);
        }
    }

    if (ans.size() != N) {
        cout << 0 << "\n";
    }
    else {
        for (const auto& a : ans) {
            cout << a << "\n";
        }
    }
}