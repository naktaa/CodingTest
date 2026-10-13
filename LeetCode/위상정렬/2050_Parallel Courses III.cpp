/*
위상정렬 dp
n <= 5e4  |  time <= 1e4
==================================================================
우선순위큐 안쓰고 따로 finish(n) 만들어서 max값 저장해놓아도 가능
dag 최장경로
*/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
    struct node {
        int to, time;
        bool operator<(const node& other) const {
            return time > other.time;
        }
    };


public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> edge(n);
        vector<int> indegree(n, 0);
        for (const auto& r : relations) {
            edge[r[0] - 1].push_back(r[1] - 1);
            indegree[r[1] - 1]++;
        }

        priority_queue<node> pq;
        for (int i = 0; i < n; i++) {
            if (indegree[i]) continue;
            pq.push({i, time[i]});
        }

        int ans = 0;
        while (!pq.empty()) {
            node now = pq.top();
            pq.pop();
            ans = now.time;

            for (const auto& next : edge[now.to]) {
                indegree[next]--;
                if (!indegree[next]) pq.push({next, now.time + time[next]});
            }
        }

        return ans;
    }
};