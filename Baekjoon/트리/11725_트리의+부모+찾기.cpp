#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    vector<vector<int>> tree(N + 1);
    vector<int> parent(N + 1, -1);
    parent[1] = 0;

    for (int i = 1; i < N; i++) {
        int n1, n2;
        cin >> n1 >> n2;
        tree[n1].push_back(n2);
        tree[n2].push_back(n1);
    }

    vector<int> visited(N + 1, 0);
    queue<int> q;
    q.push(1);
    visited[1] = 1;

    while (!q.empty()) {
        int root = q.front();
        q.pop();

        for (const auto& next : tree[root]) {
            if (visited[next]) continue;
            visited[next] = 1;
            parent[next] = root;
            q.push(next);
        }
    }

    for (int i = 2; i <= N; i++) {
        cout << parent[i] << "\n";
    }
}