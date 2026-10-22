#include <vector>
using namespace std;

vector<vector<int>> edges;
vector<int> visited;

void dfs(int now) {
    visited[now] = 1;
    for (int next : edges[now]) {
        if (visited[next]) continue;
        dfs(next);
    }
}

void runDfs(int start) {
    int len = edges.size();
    visited.assign(len, 0);
    dfs(start);
}
