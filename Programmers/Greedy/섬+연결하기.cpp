// 다익스트라?
// 모두 연결
// mst 프림 알고리즘 필요 -> 그리디

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct node {
    int to, cost;
    bool operator<(node right) const {
        return cost > right.cost;
    }
};

vector<vector<node>> island; // 섬 사이 간선 정보
int visited[100];            // 방문 여부

void find(int start, int& ans) {
    priority_queue<node> pq;
    pq.push({start, 0});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (visited[now.to] == 1) continue;
        ans += now.cost;
        visited[now.to] = 1;

        for (int i = 0; i < island[now.to].size(); i++) {
            node next = island[now.to][i];
            if (visited[next.to] == 1) continue;
            pq.push(next);
        }
    }
}

int solution(int n, vector<vector<int>> costs) {
    int ans = 0;
    island.resize(n);
    for (vector<int> cost : costs) {
        island[cost[0]].push_back({cost[1], cost[2]});
        island[cost[1]].push_back({cost[0], cost[2]});
    }

    find(0, ans); // 0에서 시작

    return ans;
}