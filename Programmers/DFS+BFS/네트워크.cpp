#include <string>
#include <vector>

using namespace std;

int ans = 0;
int visited[200];
vector<vector<int>> connect;

void find(int start) {
    for (int i = 0; i < connect[start].size(); i++) {
        int next = connect[start][i];
        if (visited[next] == 1) continue;
        visited[next] = 1;
        find(next);
    }
}

int solution(int n, vector<vector<int>> computers) {
    connect.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (computers[i][j] == 1) connect[i].push_back(j);
        }
    }

    // 0 ~ n-1 까지 탐색
    for (int i = 0; i < n; i++) {
        if (visited[i] == 1) continue;
        find(i);
        ans++;
    }

    return ans;
}