// 양방향 가중치 간선
// 가장 먼저 거치는 집하장 --> parent 필요
// 모든 시작점마다 한번씩 다익스트라 하기
// ---------------------------------------------------------------------------
// 플로이드 워셜 쓰는게 빠름 모든 정점에 대해 구하기 때문에


// ---------------------------- 다익스트라 -----------------------------------------------
// #include <iostream>
// #include <vector>
// #include <queue>
// using namespace std;
// const int INF = 21e8;

// struct node {
//     int to, time;
//     bool operator<(node other) const {
//         return time > other.time;
//     }
// };

// void dijkstra(int start, int n, vector<vector<node>>& edges) {
//     priority_queue<node> pq;
//     vector<int> dist(n, INF);
//     vector<int> path(n, -1); // 경로 저장

//     dist[start] = 0;
//     pq.push({start, 0});

//     while (!pq.empty()) {
//         node now = pq.top();
//         pq.pop();
//         if (now.time > dist[now.to]) continue;

//         for (const auto& edge : edges[now.to]) {
//             int next_time = now.time + edge.time;
//             if (next_time >= dist[edge.to]) continue;
//             dist[edge.to] = next_time;
//             path[edge.to] = now.to; // 갱신 할 때마다 path에 기록
//             pq.push({edge.to, next_time});
//         }
//     }

//     // end 지점 전부 역추적
//     for (int i = 0; i < n; i++) {
//         if (start == i) {
//             cout << "- ";
//             continue;
//         }
//         int parent = path[i];
//         int prev = i;
//         while (parent != start) {
//             prev = parent;
//             parent = path[parent];
//         }
//         cout << prev + 1 << " ";
//     }
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);

//     int n, m; // 집하장 개수, 간선 개수
//     cin >> n >> m;
//     vector<vector<node>> edges(n); // 간선

//     while (m--) {
//         int from, to, time;
//         cin >> from >> to >> time;
//         edges[from - 1].push_back({to - 1, time});
//         edges[to - 1].push_back({from - 1, time});
//     }

//     for (int i = 0; i < n; i++) {
//         dijkstra(i, n, edges);
//         cout << "\n";
//     }
// }


// ---------------------------- 플로이드 -----------------------------------------------
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m; // 집하장 개수, 간선 개수
    cin >> n >> m;
    vector<vector<int>> table(n, (vector<int>(n, INF))); // 간선
    vector<vector<int>> next(n, (vector<int>(n, -1)));   // 간선


    for (int i = 0; i < m; i++) {
        int from, to, time;
        cin >> from >> to >> time;
        table[from - 1][to - 1] = time;
        table[to - 1][from - 1] = time;
        next[from - 1][to - 1] = to - 1;
        next[to - 1][from - 1] = from - 1;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (table[i][k] + table[k][j] >= table[i][j]) continue;
                table[i][j] = table[i][k] + table[k][j];
                next[i][j] = next[i][k];
            }
        }
    }

    for (const auto& line : next) {
        for (const auto& n : line) {
            if (n == -1)
                cout << "- ";
            else
                cout << n + 1 << " ";
        }
        cout << "\n";
    }
}