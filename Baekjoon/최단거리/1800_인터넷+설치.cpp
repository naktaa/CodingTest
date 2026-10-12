// 양방향
// 연결 안되면 -1 출력
// 단순한 최단거리는 아닌 느낌
// k개 인터넷 선 없애주므로 경로 저장
// ------------------------------------------------------------------------------------
// 꼭 k개가 아니여도 k개 이하로 선택 가능
// 이분 탐색으로 비용 잡아가며 n - k개로 선택 되는지 확인
// 다익스트라 내부에서는 k개까지 무시한거 dist 2차원으로 dp 사용
// 다익스트라를 거리를 따질 필요 없이 무시한 간선 수를 따짐

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 21e8;

struct edge {
    int to, cost;
};
struct node {
    int to;
    int cnt;
    bool operator<(node other) const {
        return cnt < other.cnt;
    }
};

bool dijkstra(int target, int N, int K, const vector<vector<edge>>& edges) {
    priority_queue<node> pq;
    vector<int> dist(N + 1, INF);
    pq.push({1, 0});
    dist[1] = 0;

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.to == N) return true;
        if (now.cnt > dist[now.to]) continue;

        for (const auto& edge : edges[now.to]) {
            int nextcnt = now.cnt;
            if (edge.cost > target) nextcnt++;
            if (nextcnt > K) continue;
            if (nextcnt >= dist[edge.to]) continue;
            dist[edge.to] = nextcnt;
            pq.push({edge.to, nextcnt});
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, P, K; // 컴퓨터, 케이블, 공제
    vector<vector<edge>> edges;
    int left = 0, right = 1000000;

    cin >> N >> P >> K;
    edges.resize(N + 1);
    while (P--) {
        int from, to, dist;
        cin >> from >> to >> dist;
        edges[from].push_back({to, dist});
        edges[to].push_back({from, dist});
    }

    int ans = -1;
    // 이분 탐색으로 타겟 비용 설정
    while (left <= right) {
        int mid = (left + right) / 2;
        if (dijkstra(mid, N, K, edges)) {
            right = mid - 1;
            ans = mid;
        }
        else {
            left = mid + 1;
        }
    }
    cout << ans << "\n";
}