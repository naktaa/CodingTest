// 마을을 2개의 집합으로 나눔
// 나뉜 집합 내에서 모든 마을은 연결되어 있음
// 연결을 유지하며 길을 최소화 -> 유지비까지 최소화
// 마을은 최소 하나 이상
// 다익스트라로 구하고 가장 비용이 큰 길 잘라내기?
// dist 배열에서 거리 구하고 차이가 가장 큰 경로 빼기
// -----------------------------------------------------
// MST 써야함

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct node {
    int to, cost;
    bool operator<(node other) const {
        return cost > other.cost;
    }
};

int prim(const vector<vector<node>>& edges) {
    vector<int> visited(edges.size(), 0);
    priority_queue<node> pq;
    pq.push({0, 0});
    int sum = 0;  // 거리 합
    int MAX = -1; // cost max

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (visited[now.to]) continue; // 싸이클 형성 X
        visited[now.to] = 1;
        sum += now.cost;
        MAX = max(MAX, now.cost);

        for (const auto& next : edges[now.to]) {
            if (visited[next.to]) continue;
            pq.push(next);
        }
    }
    // cout << sum << " " << MAX << "\n";
    return sum - MAX;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; // 마을, 길
    vector<vector<node>> edges;

    cin >> N >> M;
    edges.resize(N);
    for (int i = 0; i < M; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        edges[from - 1].push_back({to - 1, cost});
        edges[to - 1].push_back({from - 1, cost});
    }

    cout << prim(edges) << "\n";
}