// 다익스트라 느낌 prim mst

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge {
    int to, weight;
    bool operator<(edge other) const {
        return weight > other.weight;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int V, E;
    vector<vector<edge>> Edge;
    int ans = 0;

    cin >> V >> E;
    Edge.resize(V + 1);
    while (E--) {
        int f, t, w;
        cin >> f >> t >> w;
        Edge[f].push_back({t, w});
        Edge[t].push_back({f, w});
    }

    priority_queue<edge> pq;
    vector<int> visited(V + 1, 0);
    pq.push({1, 0});

    while (!pq.empty()) {
        edge now = pq.top();
        pq.pop();
        if (visited[now.to]) continue;
        visited[now.to] = 1;
        ans += now.weight;

        for (const auto& next : Edge[now.to]) {
            if (visited[next.to]) continue;
            pq.push(next);
        }
    }

    cout << ans << "\n";
}