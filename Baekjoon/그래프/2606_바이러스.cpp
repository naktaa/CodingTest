#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int N, K; // 컴퓨터 수, 간선 수
    vector<vector<int>> Edge;
    vector<int> visited;
    int ans = -1;

    cin >> N >> K;
    Edge.resize(N + 1);
    visited.resize(N + 1, 0);
    while (K--) {
        int from, to;
        cin >> from >> to;
        Edge[from].push_back(to);
        Edge[to].push_back(from);
    }

    queue<int> q;
    q.push(1);
    visited[1] = 1;

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        ans++;

        for (const auto& next : Edge[now]) {
            if (visited[next]) continue;
            visited[next] = 1;
            q.push(next);
        }
    }

    cout << ans << "\n";
}