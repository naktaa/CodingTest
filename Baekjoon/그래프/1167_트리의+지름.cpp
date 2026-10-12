// 양방향, 1-based
// 임의의 정점 사이의 거리가 가장 먼 것을 구하기
// 다익스트라 반대로 --> 거리가 가장 멀 때마다 갱신?
// ----------------------------------------------------------------------
// 다익스트라는 최단 경로에만 가능
// 트리 형태이므로 가장 먼 정점으로 뻗어나가기 --> bfs
// 더이상 못 나가면 ans 랑 비교해서 max 값 갱신
// 거리가 가장 먼 정점을 2번 찾아서 마지막 정점 사이의 거리가 답
// dp로도 가능함

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

struct node {
    int to, dist;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V;                      // 정점의 개수
    vector<vector<node>> edges; // 간선의 정보
    int ans = -1;               // 답
    cin >> V;
    edges.resize(V + 1);
    for (int i = 0; i < V; i++) {
        int from;
        cin >> from;
        while (1) {
            int to, dist;
            cin >> to;
            if (to == -1) break;
            cin >> dist;
            edges[from].push_back({to, dist});
        }
    }

    vector<int> visited(V + 1, 0); // 방문여부
    int next;                      // 2번째 bfs 시작점
    int MAX = -1;
    queue<node> q;
    q.push({1, 0});
    visited[1] = 1;

    // 첫번째 bfs로 먼 정점 찾기
    while (!q.empty()) {
        node now = q.front();
        q.pop();
        if (now.dist > MAX) {
            MAX = now.dist;
            next = now.to;
        }

        for (int i = 0; i < edges[now.to].size(); i++) {
            node next = edges[now.to][i];
            int next_dist = now.dist + next.dist;
            if (visited[next.to]) continue;
            visited[next.to] = 1;
            q.push({next.to, next_dist});
        }
    }

    // 두번째 bfs로 지름 구하기
    MAX = -1;
    fill(visited.begin(), visited.end(), 0);
    q.push({next, 0});
    visited[next] = 1;

    while (!q.empty()) {
        node now = q.front();
        q.pop();
        if (now.dist > MAX) {
            MAX = now.dist;
            next = now.to;
        }

        for (int i = 0; i < edges[now.to].size(); i++) {
            node next = edges[now.to][i];
            int next_dist = now.dist + next.dist;
            if (visited[next.to]) continue;
            visited[next.to] = 1;
            q.push({next.to, next_dist});
        }
    }

    cout << MAX << "\n";
}

// cout << "\n";
// for (int i = 1; i <= V; i++) {
//     cout << i << ": ";
//     for (int j = 0; j < edges[i].size(); j++) {
//         cout << edges[i][j].to << " " << edges[i][j].dist << " | ";
//     }
//     cout << "\n";
// }