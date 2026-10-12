// 최소 개수 회선 복구 --> 간선 최소화
// 모든 정점에 대한 최단 시간 구하기 --> 다익스트라
// 쌍방향
// 1-based  1~N번 컴퓨터
// 1번부터 N까지 다익스트라값을 구해서 기존보다 더 크면 안되고 최소 회선
// 기존의 다익스트라에서 연결된 회선만 남기기?
// 경로 저장 필요
// ----------------------------------------------------------------------------
// 다익스트라를 N번 할 필요없음 - 1번하면 모든 경로에 대해 저장
// 최소 간선은 N-1개이기 때문에 무조건 중복 발생안함 --> set 사용 x 단순하게 i,parent[i]만 출력

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <set>
using namespace std;

struct node {
    int to, time;
    bool operator<(node other) const {
        return time > other.time;
    }
};
int dist[1001];
int parent[1001];          // 경로 저장용 parent
vector<vector<int>> paths; // 2 ~ N 번까지 경로

void dijkstra(vector<vector<node>>& networks) {
    for (int i = 1; i <= 1000; i++) {
        dist[i] = 21e8;
    }
    dist[1] = 0;
    priority_queue<node> pq;
    pq.push({1, 0});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.time > dist[now.to]) continue;

        for (int i = 0; i < networks[now.to].size(); i++) {
            node next = networks[now.to][i];
            int next_time = now.time + next.time;
            if (next_time >= dist[next.to]) continue;
            dist[next.to] = next_time;
            parent[next.to] = now.to; // parent 갱신
            pq.push({next.to, next_time});
        }
    }
}

int main() {
    int N, M;
    vector<vector<node>> networks; // 회선
    set<pair<int, int>> ans;
    cin >> N >> M;
    networks.resize(N + 1);
    paths.resize(N + 1); //
    for (int i = 0; i < M; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        networks[A].push_back({B, C});
        networks[B].push_back({A, C});
    }

    dijkstra(networks);
    for (int i = 2; i <= N; i++) {
        int next = i;
        while (1) {
            ans.insert({parent[next], next});
            if (parent[next] == 1) break;
            next = parent[next];
        }
    }

    cout << ans.size() << "\n";
    for (auto it = ans.begin(); it != ans.end(); it++) {
        cout << it->first << " " << it->second << "\n";
    }
}

//
// for (int i = 2; i <= N; i++) {
//     for (int j = 0; j < paths[i].size(); j++) {
//         cout << paths[i][j] << " ";
//     }
//     cout << "\n";
// }

// cout << "\n";
// for (auto it = ans.begin(); it != ans.end(); it++) {
//     cout << it->first << " " << it->second << "\n";
// }