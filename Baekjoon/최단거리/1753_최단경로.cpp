#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct node {
    int to, dist; // to, weight
    bool operator<(node right) const {
        return dist > right.dist;
    }
};
int v, e;  // 정점, 간선 개수
int start; // 시작 정점
int dist[20001];
vector<vector<node>> path;

void dijkstra() {
    // 다익스트라 시작
    priority_queue<node> pq;
    for (int i = 1; i <= v; i++) {
        dist[i] = 21e8;
    }
    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (dist[now.to] < now.dist) {
            continue;
        }
        for (int i = 0; i < path[now.to].size(); i++) {
            node next = path[now.to][i];
            int next_cost = now.dist + next.dist;
            if (next_cost >= dist[next.to]) {
                continue;
            }
            dist[next.to] = next_cost;
            pq.push({next.to, next_cost});
        }
    }
}

int main() {
    cin >> v >> e;
    path.resize(v + 1); // 1부터 v까지
    cin >> start;
    for (int i = 0; i < e; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        path[from].push_back({to, weight});
    }

    // 다익스트라 한번만
    dijkstra();

    for (int i = 1; i <= v; i++) {
        if (dist[i] == 21e8) {
            cout << "INF" << "\n";
        }
        else {
            cout << dist[i] << "\n";
        }
    }

    return 0;
}