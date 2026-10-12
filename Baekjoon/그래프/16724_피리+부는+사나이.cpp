// dfs 하면서 컴포넌트 묶기
// 컴포넌트 수가 답
// 싸이클 이루면 그대로 cnt 끼어드는 경우는 cnt--
// ========================================================================================
// 최악의 경우 스택 오버플로우 발생
// union-find 로 푸는것이 정석
// dfs 로직 개선
/*
void dfs(int y, int x) {
    state[y][x] = 1;  // 방문중

    int d = grid[y][x];
    int ny = y + diry[d];
    int nx = x + dirx[d];

    if (state[ny][nx] == 0) {
        dfs(ny, nx);
    }
    else if (state[ny][nx] == 1) {
        // 방문중인 노드를 다시 만남 -> 사이클 1개 발견
        cnt++;
    }

    state[y][x] = 2;  // 방문끝
}
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int N, M;
vector<vector<int>> grid;    // 방향
vector<vector<int>> visited; // 컴포넌트 종류  | -1: 방문 X, 0: 방문중, 1~: 컴포넌트 종류
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};
int cnt = 0;

int dfs(int y, int x) {
    if (visited[y][x] == 0) {
        return cnt;
    }
    else if (visited[y][x] > 0) {
        cnt--;
        return visited[y][x];
    }

    visited[y][x] = 0;
    int d = grid[y][x];
    int ny = y + diry[d];
    int nx = x + dirx[d];
    return visited[y][x] = dfs(ny, nx);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    grid.resize(N, vector<int>(M, 0));
    visited.resize(N, vector<int>(M, -1));
    for (int y = 0; y < N; y++) {
        string s;
        cin >> s;
        for (int x = 0; x < M; x++) {
            if (s[x] == 'R')
                grid[y][x] = 0;
            else if (s[x] == 'D')
                grid[y][x] = 1;
            else if (s[x] == 'L')
                grid[y][x] = 2;
            else if (s[x] == 'U')
                grid[y][x] = 3;
        }
    }

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (visited[y][x] != -1) continue;
            cnt++;
            dfs(y, x);
        }
    }

    cout << cnt << "\n";
}