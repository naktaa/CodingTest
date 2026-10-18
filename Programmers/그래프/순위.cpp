// n명 권투선수
// 다른 트리의 같은 레벨이 있으면 특정 X
// 위아래로 bfs 했을 때 n-1명이 있으면 순위 확정 가능

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    vector<vector<int>> edge_up(n + 1);   // 위쪽 방향 간선
    vector<vector<int>> edge_down(n + 1); // 아래 방향 간선
    int visited[n + 1];                   // 방문 여부
    for (vector<int> result : results) {
        edge_up[result[0]].push_back(result[1]);
        edge_down[result[1]].push_back(result[0]);
    }

    // 1부터 n번까지 모두 위아래로 bfs
    for (int player = 1; player <= n; player++) {
        int cnt = 0; // 위아래 특정 선수 카운트
        memset(visited, 0, sizeof(visited));
        queue<int> q;

        // 위로 bfs
        q.push(player);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            cnt++;

            for (int i = 0; i < edge_up[now].size(); i++) {
                int next = edge_up[now][i];
                if (visited[next] == 1) continue;
                visited[next] = 1;
                q.push(next);
            }
        }
        // 아래로 bfs
        q.push(player);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            cnt++;

            for (int i = 0; i < edge_down[now].size(); i++) {
                int next = edge_down[now][i];
                if (visited[next] == 1) continue;
                visited[next] = 1;
                q.push(next);
            }
        }
        // 자기 자신일 때 2번 더하므로 (n - 1) + 2 면 answer++
        if (cnt == n + 1) answer++;
    }

    return answer;
}