// 루트는 항상 1
// 루트에서 가장 거리가 먼 지점 먼저 구하고 한번 더 거리가 먼 지점을 구하면 --> 지름

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge {
    int node, weight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<vector<edge>> edges;
    vector<int> visited;
    vector<int> dist;

    cin >> N;
    edges.resize(N + 1);
    visited.resize(N + 1, 0);
    dist.resize(N + 1, 0);
    for (int i = 0; i < N - 1; i++) {
        int A, B, W;
        cin >> A >> B >> W;
        edges[A].push_back({B, W});
        edges[B].push_back({A, W});
    }

    int target = -1; // 루트에서 가장 먼 노드
    int MAX = 0;
    queue<int> q;
    q.push(1);
    visited[1] = 1;

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        target = (MAX > dist[now]) ? target : now;
        MAX = max(MAX, dist[now]);

        for (const auto& edge : edges[now]) {
            if (visited[edge.node]) continue;
            visited[edge.node] = 1;
            dist[edge.node] = dist[now] + edge.weight;
            q.push(edge.node);
        }
    }

    // 한번 더
    dist.assign(N + 1, 0);
    visited.assign(N + 1, 0);
    q.push(target);
    visited[target] = 1;
    MAX = 0;

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        MAX = max(MAX, dist[now]);

        for (const auto& edge : edges[now]) {
            if (visited[edge.node]) continue;
            visited[edge.node] = 1;
            dist[edge.node] = dist[now] + edge.weight;
            q.push(edge.node);
        }
    }

    cout << MAX << "\n";
}