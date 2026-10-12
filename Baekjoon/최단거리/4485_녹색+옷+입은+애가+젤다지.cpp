// N x N 그리드
// 그리드 한칸마다 지나가면 잃는 금액
// (0,0) --> (N-1,N-1) 가면서 잃는 금액 최소화

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 21e8;

struct node {
    int y, x, dist;
    bool operator<(node other) const {
        return dist > other.dist;
    }
};
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};

int dijkstra(int N, const vector<vector<int>>& cage) {
    vector<vector<int>> cost(N, vector<int>(N, INF));
    cost[0][0] = cage[0][0];
    priority_queue<node> pq;
    pq.push({0, 0, cage[0][0]});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.dist > cost[now.y][now.x]) continue;

        for (int i = 0; i < 4; i++) {
            int ny = now.y + diry[i];
            int nx = now.x + dirx[i];
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

            int next_cost = now.dist + cage[ny][nx];
            if (next_cost >= cost[ny][nx]) continue;
            cost[ny][nx] = next_cost;
            pq.push({ny, nx, cost[ny][nx]});
        }
    }

    return cost[N - 1][N - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;      // 동굴의 수
    int tc = 1; // 테스트케이스 번호
    while (1) {
        cin >> N;
        if (N == 0) break;
        vector<vector<int>> cage(N, vector<int>(N)); // 동굴
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                cin >> cage[y][x];
            }
        }

        cout << "Problem " << tc++ << ": " << dijkstra(N, cage) << "\n";
    }
}