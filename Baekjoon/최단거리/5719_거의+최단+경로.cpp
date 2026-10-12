// 최단 경로에 포함되지 않은 도로중 --> 가장 최단 경로
// 단방향 도로
// 0-based
// 최단경로들은 중복이 가능
// 먼저 다익스트라 해서 기존 최단거리의 경로를 모두 저장
// 중복 경로 포함하려면 다익스트라 할 때 roads에서 >= 대신 >로 해서 같은 경우도 포함
// 경로 저장해서 정점에서 경로에 해당하는 다음 정점에 대해 false 설정
// 기존에 path를 갱신시키면서 했는데 2개 이상 들어갈 때 경우 고려
// --> dist랑 거리가 같으면 그대로 push, 작으면 clear하고 push
// paths 만들었으면 다시 다익스트라 하면서 paths 지나갈 경우들은 제외
// --------------------------------------------------------------------------------
// parent 만들 때 dist보다 같으면 push만 하고 pass, 작으면 기존 parent 없애고 push
// 경로 저장할 때 parent 순회하면서 2차원 visited 사용, paths는 set 사용해야 안터짐

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <unordered_set>
using namespace std;
const int INF = 21e8;

struct node {
    int to, len; // 위치, 길이
    bool operator<(node other) const {
        return len > other.len;
    }
};

void origin_dijkstra(int start, int end, const vector<vector<node>>& roads, vector<unordered_set<int>>& paths) {
    int size = roads.size();
    vector<int> dist(size, INF);
    vector<vector<int>> parents(size); // parent

    dist[start] = 0;
    priority_queue<node> pq;
    pq.push({start, 0});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.len > dist[now.to]) continue;

        for (int i = 0; i < roads[now.to].size(); i++) {
            node next = roads[now.to][i];
            int next_len = now.len + next.len;
            if (next_len > dist[next.to]) {
                continue;
            }
            else if (next_len < dist[next.to]) {
                parents[next.to].clear(); // 기존 길이보다 작으면 모든 parent 삭제, 같으면 유지
            }
            parents[next.to].push_back(now.to); // parent에 중복으로 저장
            if (next_len == dist[next.to]) {
                continue;
            }

            dist[next.to] = next_len;
            pq.push({next.to, next_len});
        }
    }

    // end 부터 역추적하며 paths에 최단경로 저장 --> queue 이용
    int visited[501][501];
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(end);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < parents[now].size(); i++) {
            int next = parents[now][i];
            if (visited[next][now] == 1) continue;
            visited[next][now] = 1;
            paths[now].insert(next);
            q.push(next);
        }
    }
}

int next_dijkstra(int start, int end, const vector<vector<node>>& roads, const vector<unordered_set<int>>& paths) {
    int size = roads.size();
    vector<int> dist(size, INF);

    dist[start] = 0;
    priority_queue<node> pq;
    pq.push({start, 0});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.len > dist[now.to]) continue;

        for (int i = 0; i < roads[now.to].size(); i++) {
            node next = roads[now.to][i];
            bool flag = true; // 기존 최단경로에 대한 flag
            if (paths[next.to].find(now.to) != paths[next.to].end()) flag = false;
            if (!flag) continue; // 기존 최단경로 포함이면 pass

            int next_len = now.len + next.len;
            if (next_len >= dist[next.to]) continue;

            dist[next.to] = next_len;
            pq.push({next.to, next_len});
        }
    }

    return dist[end];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (1) {
        int N, M;                         // 장소 수, 도로 수
        int S, D;                         // 시작점, 도착점
        vector<vector<node>> roads;       // 도로
        vector<unordered_set<int>> paths; // 경로 저장
        cin >> N >> M;
        if (N == 0 && M == 0) break; // 마지막 입력 0 0 이면 종료
        cin >> S >> D;
        roads.resize(N);
        paths.resize(N);
        for (int i = 0; i < M; i++) {
            int U, V, P; // U에서 V로 가는 길이 P의 도로
            cin >> U >> V >> P;
            roads[U].push_back({V, P});
        }
        origin_dijkstra(S, D, roads, paths);
        int ans = next_dijkstra(S, D, roads, paths);

        if (ans == INF) ans = -1;
        cout << ans << "\n";
    }
}

// cout << "-----------------------------" << "\n";
// for (vector<int> path : paths) {
//     for (int node : path) {
//         cout << node << " ";
//     }
//     cout << "\n";
// }
// cout << "-----------------------------" << "\n";


// cout << "-----------------------------" << "\n";
// for (int len : dist) {
//     cout << len << " ";
// }
// cout << "\n";
// cout << "-----------------------------" << "\n";
// cout << "\n";