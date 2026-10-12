// 양방향
// 수색 범위 내 지역 아이템 습득 가능
// 0-based
// 다익스트라 돌리면서 소모 거리가 짧은 순서대로 pq에 집어넣으면서 진행

struct node {
    int to, dist; // 목적지, 거리
    bool operator<(node other) const {
        return dist > other.dist;
    }
};
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 21e8;

int dijkstra(int n, int m, int start, const vector<int>& items, const vector<vector<node>>& roads) {
    vector<int> dist(n, INF);
    dist[start] = 0;
    priority_queue<node> pq;
    pq.push({start, 0});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.dist > dist[now.to]) continue;

        for (int i = 0; i < roads[now.to].size(); i++) {
            node next = roads[now.to][i];
            int next_dist = now.dist + next.dist;
            if (next_dist > m) continue; // 수색범위 벗어나면 pass
            if (next_dist >= dist[next.to]) continue;
            dist[next.to] = next_dist;
            pq.push({next.to, next_dist});
        }
    }

    // 한번이라도 dist 갱신됐으면 지역 간걸로 간주
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) continue;
        sum += items[i];
    }
    return sum;
}

int main() {
    int n, m, r;                // 지역 개수, 수색 범위, 길의 개수
    vector<int> items;          // 지역에 있는 아이템 수
    vector<vector<node>> roads; // 간선
    cin >> n >> m >> r;
    items.resize(n);
    roads.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i];
    }
    for (int i = 0; i < r; i++) {
        int from, to, dist;
        cin >> from >> to >> dist;
        roads[from - 1].push_back({to - 1, dist});
        roads[to - 1].push_back({from - 1, dist});
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dijkstra(n, m, i, items, roads));
    }
    cout << ans << "\n";
}