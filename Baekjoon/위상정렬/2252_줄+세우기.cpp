#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<int> degree;
    vector<vector<int>> edge;

    cin >> N >> M;
    degree.resize(N + 1, 0);
    edge.resize(N + 1);
    while (M--) {
        int A, B;
        cin >> A >> B;
        degree[B]++;
        edge[A].push_back(B);
    }

    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (degree[i]) continue;
        q.push(i);
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        cout << now << " ";

        for (const auto& next : edge[now]) {
            degree[next]--;
            if (degree[next]) continue;
            q.push(next);
        }
    }
}