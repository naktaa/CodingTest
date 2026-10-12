// 1번 --> N번 최단 거리
// 임의의 2개 정점을 반드시 통과
// 이동했던 곳 또 이동 가능
// 정점 사이에 간선은 하나만
// 0-based로 풀기
// v1 --> v2 --> N / v2 --> v1 --> N 2가지 경우 비교

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct node {
    int num, length;
    bool operator<(node right) const {
        return length > right.length;
    }
};
int N, E;                  // 정점의 개수, 간선의 개수
vector<vector<node>> path; // a --> b 간선 정보
int v1, v2;
int dist[810];

int dijkstra(int start, int end, int temp_dist) {
    for (int i = 0; i < N; i++) {
        dist[i] = 21e8;
    }
    dist[start] = temp_dist;
    priority_queue<node> pq;
    pq.push({start, temp_dist});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.length > dist[now.num]) continue; // 다익스트라 조건
        if (now.length > dist[end]) break;        // 목적지 길이보다 크면 종료

        for (int i = 0; i < path[now.num].size(); i++) {
            node next = path[now.num][i];
            int next_dist = now.length + next.length;

            if (next_dist >= dist[next.num]) continue;
            dist[next.num] = next_dist;
            pq.push({next.num, next_dist});
        }
    }

    if (dist[end] != 21e8) {
        return dist[end];
    }
    else {
        return -1;
    }
}

int main() {
    cin >> N >> E;
    path.resize(N);
    for (int i = 0; i < E; i++) {
        int a, b, c; // a번 정점부터 b번 정점까지 거리 c의 길
        cin >> a >> b >> c;
        path[a - 1].push_back({b - 1, c});
        path[b - 1].push_back({a - 1, c});
    }
    cin >> v1 >> v2;


    int len1 = dijkstra(0, v1 - 1, 0);
    if (len1 != -1) {
        len1 = dijkstra(v1 - 1, v2 - 1, len1);
        if (len1 != -1) {
            len1 = dijkstra(v2 - 1, N - 1, len1);
        }
    }
    int len2 = dijkstra(0, v2 - 1, 0);
    if (len2 != -1) {
        len2 = dijkstra(v2 - 1, v1 - 1, len2);
        if (len2 != -1) {
            len2 = dijkstra(v1 - 1, N - 1, len2);
        }
    }

    int ans = -1;
    if (len1 != -1 && len2 != -1) {
        ans = min(len1, len2);
    }
    else if (len1 == -1) {
        ans = len2;
    }
    else if (len2 == -1) {
        ans = len1;
    }

    cout << ans;
}