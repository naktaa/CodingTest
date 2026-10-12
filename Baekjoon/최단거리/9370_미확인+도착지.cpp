// 반드시 지나가는 도로 하나 주어짐
// 목적지들 중 도로를 지나가지 않으면 없애기
// path 저장
// 목적지는 set으로 관리
// ================================================================================
// 최단경로의 거리가 여러개 가능
// 단순하게 parent 1차원으로 관리 X
// 거리 가중치 2배 하고 g - h 만 -1 해서 홀수인지 찾기

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
const int INF = 1e8;

struct edge {
    int to, dist;
    bool operator<(edge other) const {
        return dist > other.dist;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int n, m, t; // 교차로, 도로, 후보지
        int s, g, h; // 출발지, 지나간 도로(g - h)
        vector<vector<edge>> roads;
        set<int> ans;

        cin >> n >> m >> t;
        cin >> s >> g >> h;
        roads.resize(n + 1);
        while (m--) {
            int a, b, d;
            cin >> a >> b >> d;
            d *= 2;
            if ((a == g && b == h) || (a == h && b == g)) d -= 1; // 반드시 지나는 경로만 홀수로
            roads[a].push_back({b, d});
            roads[b].push_back({a, d});
        }
        while (t--) {
            int x;
            cin >> x;
            ans.insert(x);
        }

        // 다익스트라
        vector<int> dist(n + 1, INF);
        priority_queue<edge> pq;
        dist[s] = 0;
        pq.push({s, 0});

        while (!pq.empty()) {
            edge now = pq.top();
            pq.pop();
            if (now.dist > dist[now.to]) continue;

            for (const auto& next : roads[now.to]) {
                int next_dist = now.dist + next.dist;
                if (next_dist >= dist[next.to]) continue;
                dist[next.to] = next_dist;
                pq.push({next.to, next_dist});
            }
        }

        for (const int& d : ans) {
            if (dist[d] % 2 == 1) cout << d << " ";
        }

        cout << "\n";
    }
}