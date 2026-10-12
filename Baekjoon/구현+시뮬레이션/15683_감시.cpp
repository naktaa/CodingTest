// cctv 종류 5가지, -> 부터 (0 1 2 3)
// 1: 한쪽  |  2: 반대 2개  |  3: 인접 2개  |  4: 3방향  |  5: 모든 방향
// 0: 빈칸, 6: 벽
// 벽은 통과 못하고 cctv는 통과 가능
// 방향을 적절하게 설정해 사각지대 최소화시키기
// 방향 전부 따지면서 경우의수 따지기 cctv 최대 8개 -> 4^8 Max
// 재귀?
// -----------------------------------------------------------------------
// black에서 매번 visited를 복사하면 시간이 매우 증가되므로 감시 영역을 저장했다가 복원하는 방법으로 최적화 필요
// 전역이나 main에서 미리 만들어서 백트래킹 함수로 넘겨주는게 좋음

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct info {
    int y, x, type; // 좌표, 종류
    vector<int> dir;
};
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};

// CCTV 하나씩 감시 구역 계산하기
void go(int N, int M, const vector<vector<int>>& grid, const info& cctv, vector<vector<int>>& visited) {
    for (int d : cctv.dir) {
        int ny = cctv.y;
        int nx = cctv.x;

        while (1) {
            ny += diry[d];
            nx += dirx[d];
            if (ny < 0 || nx < 0 || ny >= N || nx >= M) break;  // grid 벗어나면 중지
            if (grid[ny][nx] == 6) break;                       // 벽이면 탐색 중지
            if (grid[ny][nx] > 0 && grid[ny][nx] < 6) continue; // CCTV면 통과

            visited[ny][nx] = 7; // 감시되는 지역 표시
        }
    }
}

// 사각지대 크기 구하는 함수
void black(const vector<vector<int>>& grid, const vector<info>& CCTV, const vector<vector<vector<int>>> DIR, int& ans) {
    int N = grid.size();
    int M = grid[0].size();
    int cnt = 0;                        // ans와 비교, 감시 지역 하나마다 1씩 줄여나감
    vector<vector<int>> visited = grid; // 방문 여부

    for (info cctv : CCTV) {
        go(N, M, grid, cctv, visited);
    }

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (visited[y][x] == 0) cnt++;
        }
    }

    ans = min(ans, cnt);
}

// MIN 찾는 재귀함수
void func(int depth, const vector<vector<int>>& grid, vector<info>& CCTV, const vector<vector<vector<int>>> DIR, int& ans) {
    if (depth >= CCTV.size()) {
        black(grid, CCTV, DIR, ans);
        return;
    }

    // CCTV의 종류에 따라 저장된 감시 방향마다 수행
    for (vector<int> d : DIR[depth]) {
        CCTV[depth].dir = d;
        func(depth + 1, grid, CCTV, DIR, ans);
    }
}

int main() {
    int N, M;                        // N x M 크기 (최대 8 x 8)
    vector<vector<int>> grid;        // 사무실
    vector<info> CCTV;               // cctv 위치
    vector<vector<vector<int>>> DIR; // cctv 방향 설정, 3차원으로 저장
    int ans = 21e8;                  // 답

    cin >> N >> M;
    grid.assign(N, vector<int>(M));
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            cin >> grid[r][c];
            if (grid[r][c] > 0 && grid[r][c] < 6) CCTV.push_back({r, c, grid[r][c]}); // cctv 위치 저장
            // cctv 종류에 따라 방향 저장
            switch (grid[r][c]) {
            case 1:
                DIR.push_back({{0}, {1}, {2}, {3}});
                break;
            case 2:
                DIR.push_back({{0, 2}, {1, 3}});
                break;
            case 3:
                DIR.push_back({{0, 1}, {1, 2}, {2, 3}, {3, 0}});
                break;
            case 4:
                DIR.push_back({{0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1}});
                break;
            case 5:
                DIR.push_back({{0, 1, 2, 3}});
                break;
            }
        }
    }

    func(0, grid, CCTV, DIR, ans);
    cout << ans << "\n";
}