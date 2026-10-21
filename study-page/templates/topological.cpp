#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> edges;
vector<int> indegree, ans;

bool topologicalSort() {
    int n = edges.size();
    indegree.assign(n, 0);
    ans.clear();
    for (const auto& list : edges) {
        for (int next : list) indegree[next]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        ans.push_back(now);
        for (int next : edges[now]) {
            indegree[next]--;
            if (indegree[next] == 0) q.push(next);
        }
    }
    return static_cast<int>(ans.size()) == n;
}
