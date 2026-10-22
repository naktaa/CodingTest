#include <vector>
using namespace std;

vector<vector<int>> edges;
vector<int> tin, tout, order;
int timer;

void dfs(int now, int prev) {
    tin[now] = timer;
    order[timer] = now;
    timer++;
    for (int next : edges[now]) {
        if (next == prev) continue;
        dfs(next, now);
    }
    tout[now] = timer;
}

void eulerTour(int root) { // 비어 있지 않은 트리
    int len = edges.size();
    timer = 0;
    tin.assign(len, 0);
    tout.assign(len, 0);
    order.assign(len, 0);
    dfs(root, root);
}
