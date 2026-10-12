// 단방향 간선
// parent 만들어주기

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 21e8;

struct edge {
    int to, dist;
};
struct node {
    int to, dist;
    bool operator<(node other) const {
        return dist > other.dist;
    }
};

void dijkstra(int start, int end, int N, const vector<vector<edge>>& edges) {
    priority_queue<node> pq;
    vector<int> dist(N + 1, INF);
    vector<int> parent(N + 1, -1);
    pq.push({start, 0});
    dist[start] = 0;

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.dist > dist[now.to]) continue;

        for (const auto& edge : edges[now.to]) {
            int nextdist = now.dist + edge.dist;
            if (nextdist >= dist[edge.to]) continue;
            dist[edge.to] = nextdist;
            parent[edge.to] = now.to;
            pq.push({edge.to, nextdist});
        }
    }

    int cnt = 0;
    vector<int> path;
    for (int next = end; next != -1; next = parent[next]) {
        path.push_back(next);
        cnt++;
    }

    reverse(path.begin(), path.end());
    cout << dist[end] << "\n";
    cout << cnt << "\n";
    for (const int& p : path) {
        cout << p << " ";
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<edge>> edges;
    int start, end;

    cin >> N >> M;
    edges.resize(N + 1);
    while (M--) {
        int from, to, dist;
        cin >> from >> to >> dist;
        edges[from].push_back({to, dist});
    }
    cin >> start >> end;

    dijkstra(start, end, N, edges);
}