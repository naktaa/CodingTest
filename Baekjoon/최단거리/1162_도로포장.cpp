// k개만큼의 edge 포장 가능 --> cost = 0
// 1 --> N 까지 최단 거리
// k개 그리디하게 제일 cost가 높은순?
// parent 만들어서 경로 추적해서 cost 높은 순대로 제거
// ------------------------------------------------------------------------------
// dp 문제로 생각해야함
// dist를 2차원으로 해서 K번까지 포장한 dist를 갱신
// 다익스트라 할 때 포장 안한거, 포장한거 2개 갱신하면서 진행
// node 구조체에 포장한 횟수도 추가
// 1 0 --> 2 0 or 2 1

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const long long INF = 21e17;

struct node {
    int to;
    long long cost;
    int cnt;
    bool operator<(node other) const {
        return cost > other.cost;
    }
};

long long dijkstra(int N, int K, const vector<vector<node>>& roads) {
    priority_queue<node> pq;
    vector<vector<long long>> dist(N + 1, vector<long long>(K + 1, INF)); // N개 x K번 포장
    pq.push({1, 0, 0});
    dist[1][0] = 0;

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.cost > dist[now.to][now.cnt]) continue;

        for (const auto& road : roads[now.to]) {
            // 포장 안하는 경우
            long long next_cost = now.cost + road.cost;
            if (next_cost < dist[road.to][now.cnt]) {
                dist[road.to][now.cnt] = next_cost;
                pq.push({road.to, next_cost, now.cnt});
            }
            // 포장 하는 경우
            if (now.cnt >= K) continue; // 이미 K번까지 포장했으면 더이상 포장 X
            next_cost = now.cost;
            if (next_cost < dist[road.to][now.cnt + 1]) {
                dist[road.to][now.cnt + 1] = next_cost;
                pq.push({road.to, next_cost, now.cnt + 1});
            }
        }
    }

    long long ans = INF;
    for (const auto& time : dist[N]) {
        ans = min(ans, time);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<node>> roads(N + 1);
    while (M--) {
        int from, to;
        long long cost;
        cin >> from >> to >> cost;
        roads[from].push_back({to, cost});
        roads[to].push_back({from, cost});
    }

    cout << dijkstra(N, K, roads) << "\n";
}