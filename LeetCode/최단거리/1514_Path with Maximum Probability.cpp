/*
n <= 1e4,  edges <= 2e4
다익스트라?
확률이 클수록 좋음
*/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
    using db = double;

    struct edge {
        int to;
        db dist;
    };
    struct node {
        int to;
        db dist;
        bool operator<(const node& other) const {
            return dist < other.dist;
        }
    };

public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb,
                          int start_node, int end_node) {
        vector<vector<edge>> Edge(n);
        int size = edges.size();
        for (int i = 0; i < size; i++) {
            Edge[edges[i][0]].push_back({edges[i][1], succProb[i]});
            Edge[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }

        vector<db> dist(n, 0);
        priority_queue<node> pq;
        dist[start_node] = 1;
        pq.push({start_node, 1});

        while (!pq.empty()) {
            node now = pq.top();
            pq.pop();
            if (now.dist < dist[now.to]) continue;

            for (const auto& next : Edge[now.to]) {
                db ndist = now.dist * next.dist;
                if (ndist <= dist[next.to]) continue;

                dist[next.to] = ndist;
                pq.push({next.to, ndist});
            }
        }

        return dist[end_node];
    }
};