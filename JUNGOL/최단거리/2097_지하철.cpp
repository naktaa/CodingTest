/*
다익스트라 경로 문제
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 21e8;

struct edge {
    int to, cost;
    bool operator<(edge other) const {
        return cost > other.cost;
    }
};

int main() {
    int N, M;
    vector<vector<int>> cost;

    cin >> N >> M;
    cost.resize(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> cost[i][j];
        }
    }

    priority_queue<edge> pq;
    vector<int> parent(N, -1);
    vector<int> dist(N, INF);
    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        edge now = pq.top();
        pq.pop();
        if (now.cost > dist[now.to]) continue;

        for (int i = 0; i < N; i++) {
            int next_cost = now.cost + cost[now.to][i];
            if (next_cost >= dist[i]) continue;
            dist[i] = next_cost;
            pq.push({i, next_cost});
            parent[i] = now.to;
        }
    }

    cout << dist[M - 1] << "\n";
    vector<int> path;
    for (int i = M - 1; i != -1; i = parent[i]) {
        path.push_back(i + 1);
    }
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i] << " ";
    }
}