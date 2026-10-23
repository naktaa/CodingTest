#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;
const int INF = 21e8;

struct node {
    int to, dist;
    bool operator<(const node& other) const {
        return dist > other.dist;
    }
};

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pii>> edges(n);
        for (const auto& time : times) {
            edges[time[0] - 1].push_back({time[1] - 1, time[2]});
        }

        priority_queue<node> pq;
        vector<int> dist(n, INF);
        dist[k - 1] = 0;
        pq.push({k - 1, 0});

        while (!pq.empty()) {
            node now = pq.top();
            pq.pop();
            if (now.dist > dist[now.to]) continue;

            for (auto& [next, d] : edges[now.to]) {
                int ndist = now.dist + d;
                if (ndist >= dist[next]) continue;
                dist[next] = ndist;
                pq.push({next, ndist});
            }
        }

        int ans = -1;
        for (const int& d : dist) {
            ans = max(ans, d);
        }
        return (ans == INF ? -1 : ans);
    }
};