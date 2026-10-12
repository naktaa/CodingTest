#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> edges(N);
    vector<int> visited(N, 0);

    for (int i = 0; i < M; i++) {
        int from, to;
        cin >> from >> to;
        edges[from - 1].push_back(to - 1);
        edges[to - 1].push_back(from - 1);
    }

    int ans = 0;
    queue<int> q;

    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;
        q.push(i);

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            visited[now] = 1;

            for (const auto& n : edges[now]) {
                if (visited[n]) continue;
                visited[n] = 1;
                q.push(n);
            }
        }
        ans++;
    }

    cout << ans << "\n";
}