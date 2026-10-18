// 모든 wire 한번씩 삭제하면서 계산
// 1 ~ n --> 0-based로 바꾸기

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

void func(int index, int n, vector<vector<int>> wires, int& answer) {
    vector<vector<int>> node(n); // 양방향 연결
    int visited[n];              // 방문 여부
    int cnt1 = 0;
    int cnt2 = 0;
    int flag = 0;
    memset(visited, 0, sizeof(visited));

    // 노드 연결집합 만들어주기
    for (int i = 0; i < wires.size(); i++) {
        if (index == i) continue;
        int from = wires[i][0] - 1; // 0-based
        int to = wires[i][1] - 1;   // 0-based
        node[from].push_back(to);
        node[to].push_back(from);
    }

    for (int i = 0; i < n; i++) {
        if (visited[i] == 1) continue;
        queue<int> q; // bfs 큐
        q.push(i);
        visited[i] = 1;
        if (cnt1 > 0) flag = 1;

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            if (flag == 0)
                cnt1++;
            else
                cnt2++;

            // 연결된 노드들 큐에 삽입
            for (int next : node[now]) {
                if (visited[next] == 1) continue;
                visited[next] = 1;
                q.push(next);
            }
        }
    }

    int dif = abs(cnt1 - cnt2); // 개수 차이 return
    if (dif < answer) answer = dif;
}

int solution(int n, vector<vector<int>> wires) {
    int answer = 21e8;

    for (int i = 0; i < wires.size(); i++) {
        func(i, n, wires, answer);
    }

    return answer;
}