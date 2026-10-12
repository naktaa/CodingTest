#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;


int n, m;                // 문제, 정보
vector<int> node[32001]; // 노드 간선 저장
int degree[32001];       // 인접차수 저장


int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        node[from].push_back(to);
        degree[to]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        int now = pq.top();
        pq.pop();
        cout << now << " ";

        for (int i = 0; i < node[now].size(); i++) {
            int next = node[now][i];
            degree[next]--;
            if (degree[next] == 0) pq.push(next);
        }
    }

    return 0;
}