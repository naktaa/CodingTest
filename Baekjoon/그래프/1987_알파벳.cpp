// 지금까지 만난 알파벳 중복 X
// 최대로 지나갈 수 있는 칸 수 구하기
// 왔던길로 어차피 중복해서 못가기 때문에 visited 필요 X
// 지금까지 만난 알파벳만 저장
// 백트래킹으로
// ----------------------------------------------------------------------------------------
// set 쓰면서 dfs bfs 하면 터질 확률 높음 --> 그냥 배열로 확인

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;

int R, C;
vector<string> grid;
int alphas[26];
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};
int ans = 1;

void dfs(int y, int x, int cnt) {
    for (int i = 0; i < 4; i++) {
        int ny = y + diry[i];
        int nx = x + dirx[i];

        if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue; // grid 체크
        if (alphas[grid[ny][nx] - 'A']) continue;             // 알파벳 중복 체크

        alphas[grid[ny][nx] - 'A'] = 1;
        dfs(ny, nx, cnt + 1);
        alphas[grid[ny][nx] - 'A'] = 0;
    }
    ans = max(ans, cnt);
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        string line;
        cin >> line;
        grid.push_back(line);
    }

    alphas[grid[0][0] - 'A'] = 1;
    dfs(0, 0, 1);

    cout << ans << "\n";
}