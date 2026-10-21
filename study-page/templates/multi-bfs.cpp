#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> edges;
vector<int> starts, dist;

void multiBfs() {
    dist.assign(edges.size(), -1);
    queue<int> q;
    for (int start : starts) {
        if (dist[start] != -1) continue;
        dist[start] = 0;
        q.push(start);
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int next : edges[now]) {
            if (dist[next] != -1) continue;
            dist[next] = dist[now] + 1;
            q.push(next);
        }
    }
}
