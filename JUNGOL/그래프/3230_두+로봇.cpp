// 같은 edge 위에 있으면 통신 가능
// dfs 하면서 목표점 도착할 때 까지 가장 긴 dist 저장해놓고 거리 합에서 빼기

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct edge {
    int to, dist;
};
struct path {
    int no, sum, max;
};

int main() {
    int N, r1, r2;
    vector<vector<edge>> tree;

    cin >> N >> r1 >> r2;
    r1--, r2--;
    tree.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int from, to, dist;
        cin >> from >> to >> dist;
        tree[from - 1].push_back({to - 1, dist});
        tree[to - 1].push_back({from - 1, dist});
    }

    queue<path> q;
    vector<int> visited(N, 0);
    q.push({r1, 0, 0});
    visited[r1] = 1;

    while (!q.empty()) {
        path now = q.front();
        q.pop();
        if (now.no == r2) {
            cout << now.sum - now.max;
            return 0;
        }

        for (const edge& next : tree[now.no]) {
            if (visited[next.to]) continue;
            visited[next.to] = 1;
            int nmax = max(next.dist, now.max);
            q.push({next.to, now.sum + next.dist, nmax});
        }
    }
}