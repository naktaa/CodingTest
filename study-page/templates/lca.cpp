#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> edges, parent;
vector<int> depth;
int LOG;

void buildLca(int root) { // 0-based, 비어 있지 않은 연결 트리
    int len = edges.size();
    LOG = 1;
    while ((1 << LOG) <= len) LOG++;
    parent.assign(LOG, vector<int>(len, root));
    depth.assign(len, -1);
    queue<int> q;
    depth[root] = 0;
    parent[0][root] = root;
    q.push(root);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int next : edges[now]) {
            if (depth[next] != -1) continue;
            depth[next] = depth[now] + 1;
            parent[0][next] = now;
            q.push(next);
        }
    }
    for (int k = 1; k < LOG; k++) {
        for (int v = 0; v < len; v++) {
            parent[k][v] = parent[k - 1][parent[k - 1][v]];
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for (int k = 0; k < LOG; k++) {
        if (diff & (1 << k)) a = parent[k][a];
    }
    if (a == b) return a;
    for (int k = LOG - 1; k >= 0; k--) {
        if (parent[k][a] == parent[k][b]) continue;
        a = parent[k][a];
        b = parent[k][b];
    }
    return parent[0][a];
}
