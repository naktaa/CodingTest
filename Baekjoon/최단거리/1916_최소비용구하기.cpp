#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;


struct node {
    int to, dist;
    bool operator<(node right) const {
        return dist > right.dist;
    }
};
int n, m;       // 도시, 버스 개수
int START, END; // 출발, 도착 도시
vector<vector<node>> bus;
int dist[1001];

void dijkstra() {
    priority_queue<node> pq;
    for (int i = 1; i <= n; i++) {
        dist[i] = 21e8;
    }
    dist[START] = 0;
    pq.push({START, 0});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (dist[now.to] < now.dist) {
            continue;
        }

        for (int i = 0; i < bus[now.to].size(); i++) {
            node next = bus[now.to][i];
            int next_cost = dist[now.to] + next.dist;
            if (next_cost >= dist[next.to]) {
                continue;
            }
            dist[next.to] = next_cost;
            pq.push({next.to, next_cost});
        }
    }
}

int main() {
    cin >> n;
    cin >> m;
    bus.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        bus[from].push_back({to, cost});
    }
    cin >> START >> END;

    dijkstra();

    cout << dist[END];
}