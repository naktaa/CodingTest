// 1-based, NxN
// 다음칸에 머리 --> 사과 있으면 사과 없어지고 꼬리 그대로
//              --> 사과 없으면 꼬리칸 비워짐
// 벽이나 자기자신에 부딪히면 끝
// 처음 오른쪽 향한채로 (1,1) 시작
// 시작과 끝만 판단하면서 gird에 몸이 어디에 위치해있는지 표시
// grid에 dir 저장해서 tail 위치 갱신정보 알기 --> head 이동할때마다 이전 위치에 방향 저장
// ------------------------------------------------------------------------------------------
// 방향 설정할 때 음수로 -1이 아니라 +3으로 만들어주기
// 사과 먹고 그 자리의 사과 제거하는 로직 보충
// @@ deque를 사용하면 front에 머리 좌표 추가하고 back에서 꼬리 제거하기 편함

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct coord {
    int y, x;
};
int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};

int main() {
    int N, K, L;                       // 보드 크기, 사과의 개수, 방향 변환 횟수
    vector<vector<int>> board;         // 보드
    queue<pair<int, char>> dir_change; // 방향 변환 정보
    cin >> N >> K;
    board.resize(N + 1, vector<int>(N + 1, 0)); // 1-based의 NxN 그리드로 만들어줌
    for (int i = 0; i < K; i++) {
        int R, C; // 행 열
        cin >> R >> C;
        board[R][C] = 1;
    }
    cin >> L;
    for (int i = 0; i < L; i++) {
        int X;
        char C;
        cin >> X >> C;
        dir_change.push({X, C});
    }

    // 게임 시작
    vector<vector<int>> grid(N + 1, vector<int>(N + 1, -1)); // 몸의 위치 및 방향 정보 표시
    int TIME = 0;                                            // 게임 시간
    int DIR = 0;                                             // 현재 방향 (오른쪽 시작)
    coord head = {1, 1};
    coord tail = {1, 1};
    pair<int, char> next_dir = dir_change.front();
    dir_change.pop();

    while (1) {
        // 시간마다 방향 변환 확인
        if (TIME == next_dir.first) {
            if (next_dir.second == 'D') {
                DIR = (DIR + 1) % 4;
            }
            else {
                DIR = (DIR + 3) % 4;
            }
            // 다음 방향 변환 정보 갱신
            if (!dir_change.empty()) {
                next_dir = dir_change.front();
                dir_change.pop();
            }
        }
        TIME++;

        grid[head.y][head.x] = DIR; // 이전 위치에 방향 저장해 다음 위치 정보 남김
        int ny = head.y + diry[DIR];
        int nx = head.x + dirx[DIR];
        if (ny < 1 || nx < 1 || ny > N || nx > N) break; // 보드 벗어나면 종료
        if (grid[ny][nx] > -1) break;                    // 자기 자신과 부딪히면 종료

        head = {ny, nx};
        if (board[ny][nx] == 0) {
            int ndir = grid[tail.y][tail.x]; // 현재 tail의 dir 저장
            grid[tail.y][tail.x] = -1;       // 사과 없으면 tail 위치 비우기
            tail.y += diry[ndir];
            tail.x += dirx[ndir];
        }
        else {
            board[ny][nx] = 0;
        }
    }

    cout << TIME << "\n";
}