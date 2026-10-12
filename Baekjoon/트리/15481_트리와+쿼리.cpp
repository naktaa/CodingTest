// =================================
// visited 배열 대신 dfs 함수 자체에 부모 node를 인자로 받아서 방문 안하게 처리 하면 좋음

#include <iostream>
#include <vector>
using namespace std;

int N, R, Q;               // 정점, 루트 번호, 쿼리
vector<vector<int>> edges; // 간선
vector<int> query;
vector<int> treeCnt;
vector<int> visited;

int Count(int node) {
    treeCnt[node] = 1;
    for (const auto& subtree : edges[node]) {
        if (visited[subtree]) continue;
        visited[subtree] = 1;
        treeCnt[node] += Count(subtree);
    }

    return treeCnt[node];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> R >> Q;
    edges.resize(N + 1);
    treeCnt.resize(N + 1, 0);
    visited.resize(N + 1, 0);
    for (int i = 0; i < N - 1; i++) {
        int from, to;
        cin >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    while (Q--) {
        int q;
        cin >> q;
        query.push_back(q);
    }

    visited[R] = 1;
    Count(R);

    for (const auto& q : query) {
        cout << treeCnt[q] << "\n";
    }
}