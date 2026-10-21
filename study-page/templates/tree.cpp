#include <vector>
using namespace std;

vector<vector<int>> edges;
vector<int> parent, depth, order;

void dfs(int now, int prev) {
    parent[now] = prev;
    order.push_back(now);
    for (int next : edges[now]) {
        if (next == prev) continue;
        depth[next] = depth[now] + 1;
        dfs(next, now);
    }
}

void traverse(int root) { // edges는 비어 있지 않은 트리
    parent.assign(edges.size(), -1);
    depth.assign(edges.size(), 0);
    order.clear();
    dfs(root, root);
}
