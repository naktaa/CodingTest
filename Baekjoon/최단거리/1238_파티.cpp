// N개 마을, M개 단방향 도로
// 목표 마을로 갔다가 돌아오기
// 1-based

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

struct node {
    int to, time;
    bool operator<(node other) const {
        return time > other.time; // 오름차순으로 정렬
    }
};

int dist[1001]; // 다익스트라용 걸린 시간

// 시작점, 끝점, 걸린 시간, 간선, 답
void dijkstra(int start, int end, int time, vector<vector<node>> edge, int& ans) {
    for (int i = 1; i <= edge.size() - 1; i++) {
        dist[i] = 21e8;
    }
    priority_queue<node> pq;
    pq.push({start, time});
    dist[start] = time;

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.time > dist[now.to]) continue;

        for (int i = 0; i < edge[now.to].size(); i++) {
            node next = edge[now.to][i];
            int next_time = now.time + next.time;
            if (next_time >= dist[next.to]) continue;
            dist[next.to] = next_time;
            pq.push({next.to, next_time});
        }
    }

    ans = max(ans, dist[end]);
}

int main() {
    int N, M, X; // 마을 수, 도로 수, 목표 마을
    int ans = -1;
    cin >> N >> M >> X;
    vector<vector<node>> edge(N + 1); // N개 마을의 간선들
    for (int i = 0; i < M; i++) {
        int from, to, time;
        cin >> from >> to >> time;
        edge[from].push_back({to, time}); // 양방향 X
    }

    for (int start = 1; start <= N; start++) {
        dijkstra(start, X, 0, edge, ans);
        dijkstra(X, start, dist[X], edge, ans);
    }

    cout << ans << "\n";
}