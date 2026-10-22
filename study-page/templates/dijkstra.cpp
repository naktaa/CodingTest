#include <queue>
#include <vector>
using namespace std;
using ll = long long;

const ll INF = 1'000'000'000'000'000'000LL;

struct edge {
    int to, weight;
};

struct node {
    ll cost;
    int idx;

    bool operator<(const node& next) const {
        return cost > next.cost; // 작은 거리부터 꺼내는 최소 힙
    }
};

vector<vector<edge>> edges;
vector<ll> dist;

void dijkstra(int start) { // N <= 200000, 0 <= weight <= 10^9
    int len = edges.size();
    dist.assign(len, INF);
    priority_queue<node> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        node top = pq.top();
        pq.pop();
        ll cost = top.cost;
        int now = top.idx;
        if (cost != dist[now]) continue;
        for (edge next : edges[now]) {
            ll nextCost = cost + next.weight;
            if (nextCost >= dist[next.to]) continue;
            dist[next.to] = nextCost;
            pq.push({nextCost, next.to});
        }
    }
}
