/*
행성 간 거리 --> x, y, z 맨해튼 거리 중 min
그냥 MST하면 터짐
======================================================================
x, y, z 각각 정렬
인접 행성들끼리의 간선 set 만들기
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;
using pr = pair<int, ll>;

struct edge {
    int to;
    ll dist;
    bool operator<(edge other) const {
        return dist > other.dist;
    }
};

bool cmp(pr A, pr B) {
    return A.second < B.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<vector<pr>> coord;
    vector<vector<edge>> edges;
    vector<int> visited;
    int ans = 0;

    cin >> N;
    coord.resize(3, vector<pr>(N));
    edges.resize(N);
    visited.resize(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> coord[0][i].second >> coord[1][i].second >> coord[2][i].second;
        coord[0][i].first = coord[1][i].first = coord[2][i].first = i;
    }

    for (int i = 0; i < 3; i++) {
        sort(coord[i].begin(), coord[i].end(), cmp);
    }

    for (int j = 0; j < N - 1; j++) {
        for (int i = 0; i < 3; i++) {
            ll dist = coord[i][j + 1].second - coord[i][j].second;
            edges[coord[i][j + 1].first].push_back({coord[i][j].first, dist});
            edges[coord[i][j].first].push_back({coord[i][j + 1].first, dist});
        }
    }

    // prim MST
    priority_queue<edge> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        edge now = pq.top();
        pq.pop();
        if (visited[now.to]) continue;
        visited[now.to] = 1;
        ans += now.dist;

        for (const auto& next : edges[now.to]) {
            if (visited[next.to]) continue;
            pq.push(next);
        }
    }

    cout << ans << "\n";
}