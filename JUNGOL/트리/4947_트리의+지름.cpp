/*
최상위 루트에서 양쪽으로 재보기
양쪽으로 bfs해서 길이 더하기
======================================================
한 지점에서 가장 먼 곳 구하고 한번 더 가장 먼 곳 거리 재면 지름
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using pr = pair<int, int>;

int main() {
    int N;
    vector<vector<int>> tree;

    cin >> N;
    tree.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a - 1].push_back(b - 1);
        tree[b - 1].push_back(a - 1);
    }

    int edge = -1;
    vector<int> visited(N, 0);
    queue<int> q;
    q.push(0);
    visited[0] = 1;

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        edge = now;

        for (const auto& next : tree[now]) {
            if (visited[next]) continue;
            visited[next] = 1;
            q.push(next);
        }
    }

    queue<pr> q2;
    visited.assign(N, 0);
    q2.push({edge, 0});
    visited[edge] = 1;
    int ans = 0;

    while (!q2.empty()) {
        pr now = q2.front();
        q2.pop();
        ans = now.second;

        for (const auto& next : tree[now.first]) {
            if (visited[next]) continue;
            visited[next] = 1;
            q2.push({next, now.second + 1});
        }
    }

    cout << ans << "\n";
}