// 최단경로 오름차순 중 k번째 구하기
// 1-based
// 단방향
// 경로를 저장해놓고 제외하기?
// 다익스트라 한번씩 하면서 path에 경로 저장
// 이전 다익스트라 parent가 기록되어 있을 때 parent
// ---------------------------------------------------------------------------
// dist 배열도 pq로 구현
// k개만큼 채워질때까지 push 하고 k개일때는 max와 비교해서 작을때만 갱신

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 21e8;

struct node {
    int to, time;
    bool operator<(node other) const {
        return time > other.time;
    }
};

void dijkstra(int n, int k, const vector<vector<node>>& roads, vector<priority_queue<int, vector<int>, less<int>>>& dist) {
    priority_queue<node> pq;
    pq.push({1, 0});
    dist[1].push(0);

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();

        if (dist[now.to].size() == k && now.time > dist[now.to].top()) continue;

        for (int i = 0; i < roads[now.to].size(); i++) {
            node next = roads[now.to][i];
            int next_time = now.time + next.time;

            if (dist[next.to].size() < k) {
                dist[next.to].push(next_time);
                pq.push({next.to, next_time});
            }
            else {
                if (next_time < dist[next.to].top()) {
                    dist[next.to].pop();
                    dist[next.to].push(next_time);
                    pq.push({next.to, next_time});
                }
            }
        }
    }
}

int main() {
    int n, m, k; // 도시, 도로, k번째 최단경로
    cin >> n >> m >> k;
    vector<vector<node>> roads(n + 1);
    vector<priority_queue<int, vector<int>, less<int>>> dist(n + 1); // 내림차순 dist
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        roads[a].push_back({b, c});
    }

    dijkstra(n, k, roads, dist);

    // size가 k가 아닌 dist에 -1 push
    for (int i = 1; i <= n; i++) {
        if (dist[i].size() < k) {
            cout << -1 << "\n";
        }
        else {
            cout << dist[i].top() << "\n";
        }
    }
}