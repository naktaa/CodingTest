// 양방향 가중치 길
// 1 --> N 까지의 최소 비용

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 21e8;

struct node {
    int to, cost;
    bool operator<(node other) const {
        return cost > other.cost;
    }
};

int dijkstra(int N, const vector<vector<node>>& edges) {
    priority_queue<node> pq;
    vector<int> dist(N + 1, INF);
    pq.push({1, 0});
    dist[1] = 0;

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.cost > dist[now.to]) continue;

        for (const auto& edge : edges[now.to]) {
            int next_cost = now.cost + edge.cost;
            if (next_cost >= dist[edge.to]) continue;
            dist[edge.to] = next_cost;
            pq.push({edge.to, next_cost});
        }
    }

    return dist[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<vector<node>> edges(N + 1);
    while (M--) {
        int from, to, cost;
        cin >> from >> to >> cost;
        edges[from].push_back({to, cost});
        edges[to].push_back({from, cost});
    }

    cout << dijkstra(N, edges) << "\n";
}