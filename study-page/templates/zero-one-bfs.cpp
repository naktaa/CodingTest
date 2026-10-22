#include <deque>
#include <vector>
using namespace std;

const int INF = 1'000'000'000;

struct edge {
    int to, weight; // weight는 0 또는 1
};

struct node {
    int cost, idx;
};

vector<vector<edge>> edges;
vector<int> dist;

void zeroOneBfs(int start) { // N <= 200000
    int len = edges.size();
    dist.assign(len, INF);
    deque<node> dq;
    dist[start] = 0;
    dq.push_front({0, start});
    while (!dq.empty()) {
        node top = dq.front();
        dq.pop_front();
        int cost = top.cost;
        int now = top.idx;
        if (cost != dist[now]) continue;
        for (edge next : edges[now]) {
            int nextCost = cost + next.weight;
            if (nextCost >= dist[next.to]) continue;
            dist[next.to] = nextCost;
            if (next.weight == 0) dq.push_front({nextCost, next.to});
            else dq.push_back({nextCost, next.to});
        }
    }
}
