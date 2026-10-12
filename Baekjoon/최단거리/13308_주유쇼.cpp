// 양방향 간선 N개 정점 M개 간선
// 1 --> N
// 도시마다 주유소 가격 | 간선마다 거리
// 기름 넣으면서 N번 까지 가는 최소비용
// 지금까지 지나온 도시의 리터당 가격을 계속해서 저장 --> 제일 작은거 사용
// ===================================================================================================
// cost 를 2차원으로 확장해서 cost_min 까지 저장

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;
const ll INF = 1e18;

struct edge {
    int to;
    ll dist;
};
struct node {
    int to;
    ll cost, price_min;
    bool operator<(node other) const {
        return cost > other.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; // 도시, 도로
    vector<vector<edge>> roads;
    vector<ll> price; // 도시별 리터당 가격
    ll price_max = 0;

    cin >> N >> M;
    roads.resize(N + 1);
    price.resize(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> price[i];
        price_max = max(price_max, price[i]);
    }
    for (int i = 0; i < M; i++) {
        int f, t, d;
        cin >> f >> t >> d;
        roads[f].push_back({t, d});
        roads[t].push_back({f, d});
    }

    // 다익스트라
    vector<vector<ll>> cost(N + 1, vector<ll>(price_max + 1, INF));
    priority_queue<node> pq;
    pq.push({1, 0, price_max});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.cost > cost[now.to][now.price_min]) continue;
        now.price_min = min(now.price_min, price[now.to]);
        // cout << now.to << " city: cost = " << now.cost << ", price = " << now.price_min << "\n";

        for (const auto& next : roads[now.to]) {
            ll next_cost = now.cost + next.dist * now.price_min;
            if (next_cost >= cost[next.to][now.price_min]) continue;
            cost[next.to][now.price_min] = next_cost;
            pq.push({next.to, next_cost, now.price_min});
        }
    }

    ll ans = INF;
    for (int i = 1; i <= price_max; i++) {
        ans = min(ans, cost[N][i]);
    }
    cout << ans << "\n";
}