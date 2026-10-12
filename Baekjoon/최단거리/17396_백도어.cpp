// 양방향 간선
// ai 가 1인곳은 못감 도착점 제외
// 0 --> N - 1 까지 최단 거리

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;
const ll INF = 1e16;

struct node {
    int to;
    ll time;
    bool operator<(node other) const {
        return time > other.time;
    }
};

ll dijkstra(int N, const vector<vector<node>>& edges, const vector<int>& ward) {
    priority_queue<node> pq;
    vector<ll> dist(N, INF);
    pq.push({0, 0});
    dist[0] = 0;

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.time > dist[now.to]) continue;

        for (const auto& edge : edges[now.to]) {
            ll next_time = now.time + edge.time;
            if (next_time >= dist[edge.to]) continue;
            // if (ward[edge.to] && edge.to != N - 1) continue; // 시야에 있으면 pass
            dist[edge.to] = next_time;
            pq.push({edge.to, next_time});
        }
    }

    return (dist[N - 1] == INF) ? -1 : dist[N - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    vector<vector<node>> edges(N);
    vector<int> ward;
    for (int i = 0; i < N; i++) {
        int n;
        cin >> n;
        ward.push_back(n);
    }
    for (int i = 0; i < M; i++) {
        int from, to;
        ll time;
        cin >> from >> to >> time;
        // 시야에 보이면 간선 push 안함
        if (ward[from] || ward[to]) {
            if (from != N - 1 && to != N - 1) continue;
        }
        edges[from].push_back({to, time});
        edges[to].push_back({from, time});
    }

    cout << dijkstra(N, edges, ward) << "\n";
}