// N개 도시에 K개의 면접장
// 단방향 도로 여러개도 가능
// 각 도시에서 면접장까지 거리 중 가장 가까운 걸 먼저 구해서 return
// 면접장에서 거리가 가장 먼 도시의 번호와 거리 구하기
// 플로이드 워셜? N이 10만개가 최대라 X
// 주어진 면접장 위치에서 모두 다익스트라 돌려보기
// ----------------------------------------------------------------------------------------------------
// 면접장에서 도시로 가는걸 역간선 생각
// 모든 면접장을 한번에 pq에 넣어서 다익스트라를 1번만
// start 지점을 여러개 넣고 다익스트라 돌리는것도 가능 parnet 추적하려면 따로 배열 하나 더 만들기

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;
const ll INF = 21e15;

struct edge {
    int to;
    ll dist;
};
struct node {
    int to;
    ll dist;
    bool operator<(node other) const {
        return dist > other.dist;
    }
};

void dijkstra(const vector<vector<edge>>& edges, const vector<int>& interview, int N, int& ans_num, ll& ans_dist) {
    priority_queue<node> pq;
    vector<ll> dist(N + 1, INF);
    for (const auto& start : interview) {
        pq.push({start, 0});
        dist[start] = 0;
    }

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.dist > dist[now.to]) continue;

        for (const auto& edge : edges[now.to]) {
            ll next_dist = now.dist + edge.dist;
            if (next_dist >= dist[edge.to]) continue;
            dist[edge.to] = next_dist;
            pq.push({edge.to, next_dist});
        }
    }

    for (int i = 1; i <= N; i++) {
        if (dist[i] == INF) continue; // 못 가는 곳은 pass
        if (dist[i] > ans_dist) {
            ans_num = i;
            ans_dist = dist[i];
        }
        else if (dist[i] == ans_dist) {
            ans_num = min(ans_num, i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K;                // 도시, 도로, 면접장
    vector<vector<edge>> edges; // 도로
    vector<int> interview;      // 면접장 번호
    int ans_num = 1;
    ll ans_dist = -1;

    cin >> N >> M >> K;
    edges.resize(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        // if (!edges[v].empty() && c >= edges[v][0].dist) continue; // 이미 간선이 존재하고 간선의 dist 보다 크면 pass
        edges[v].push_back({u, c}); // 역방향으로 간선 저장
    }
    for (int i = 0; i < K; i++) {
        int k;
        cin >> k;
        interview.push_back(k);
    }

    dijkstra(edges, interview, N, ans_num, ans_dist);
    cout << ans_num << "\n";
    cout << ans_dist << "\n";
}