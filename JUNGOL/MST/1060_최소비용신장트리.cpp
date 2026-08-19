/*
MST 프림으로 해보기
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge {
    int to, cost;
    bool operator<(edge other) const {
        return cost > other.cost;
    }
};

int main() {
    int N;
    vector<vector<int>> Cost;

    cin >> N;
    Cost.resize(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> Cost[i][j];
        }
    }

    priority_queue<edge> q;
    int ans = 0;
    vector<int> visited(N, 0);
    q.push({0, 0});

    while (!q.empty()) {
        edge now = q.top();
        q.pop();
        if (visited[now.to]) continue;
        visited[now.to] = 1;
        ans += now.cost;

        for (int i = 0; i < N; i++) {
            if (visited[i]) continue;
            q.push({i, Cost[now.to][i]});
        }
    }

    cout << ans << "\n";
}