/*
N <= 1000,  -1e6 <= 좌표 <= 1e6
점 사이의 거리 -> 맨해튼 거리
모든 점을 연결하는 최소 비용
MST?
모든 노드 조합에 대해 거리 구하고 진행
*/

#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
using ll = long long;
using pr = pair<int, int>;

struct node {
    int to;
    ll dist;
    bool operator<(const node other) const {
        return dist > other.dist;
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int len = points.size();
        vector<vector<pr>> edges(len);
        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                ll dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                edges[i].push_back({j, dist});
                edges[j].push_back({i, dist});
            }
        }

        priority_queue<node> pq;
        vector<int> visited(len, 0);
        ll MIN = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            node now = pq.top();
            pq.pop();
            if (visited[now.to]) continue;

            visited[now.to] = 1;
            MIN += now.dist;

            for (const auto& next : edges[now.to]) {
                auto [to, dist] = next;
                if (visited[to]) continue;
                pq.push({to, dist});
            }
        }

        return MIN;
    }
};