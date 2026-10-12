// 2개의 집합이 모두 속한 정점들이 인접하면 안됨
// A, B 각각 정점들이 인접 X
// 순서대로 2개 set에 넣으면서 안되면 끝
// 큐에다 넣고 하나씩 하기
// ----------------------------------------------------
// 모두 연결 안된 경우도 고려해서 V개 만큼 q에 넣는 과정 추가

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int K;                     // 테케 개수
int V, E;                  // 정점, 간선
vector<vector<int>> edges; // 간선
vector<int> BiGraph;       // 두개의 집합 1 -1 로 구분

struct node {
    int to, graph; // from, to, 집합 종류
};

void input() {
    cin >> V >> E;
}

void init() {
    edges.clear();
    edges.resize(V);      // 정점 개수만큼 크기 초기화
    BiGraph.assign(V, 0); // 0 으로 초기화
}

void solution() {
    queue<node> q;
    for (int n = 0; n < V; n++) {
        if (BiGraph[n]) continue;
        BiGraph[n] = 1;
        q.push({n, 1});

        while (!q.empty()) {
            node now = q.front();
            q.pop();

            for (int i = 0; i < edges[now.to].size(); i++) {
                int next = edges[now.to][i];
                // 현재 노드의 집합과 인접 노드의 집합이 같으면 NO 출력
                if (BiGraph[now.to] == BiGraph[next]) {
                    cout << "NO" << "\n";
                    return;
                }
                if (BiGraph[next]) continue; // 집합 정해져있으면 이미 q에 넣었으므로 pass

                BiGraph[next] = -BiGraph[now.to];
                q.push({next, -BiGraph[now.to]});
            }
        }
    }
    cout << "YES" << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> K;
    for (int tc = 1; tc <= K; tc++) {
        input();
        init();
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            edges[u - 1].push_back(v - 1); // 0-index로 바꿈
            edges[v - 1].push_back(u - 1);
        }
        solution();
    }
}