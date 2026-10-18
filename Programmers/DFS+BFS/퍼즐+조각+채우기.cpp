// 테트리스, 흰칸 채워넣기 50X50크기
// 최대한 빈칸 얼마나 채울 수 있는지
// 회전 가능
// 조각 넣었을 때 빈칸이 있으면 안됨
// table에서 먼저 조각 정보 --> 그리드 0 1 정보를 그대로 떠서 저장
// 3차원으로 그리드 저장

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct coord {
    int y, x;
};

int diry[] = {0, 1, 0, -1};
int dirx[] = {1, 0, -1, 0};
int visited[50][50]; // 방문 여부

// table의 조각들 저장
// 기존 table, 조각 시작 y, 조각 시작 x, 조각 저장할 3차원 벡터
void table_save(vector<vector<int>> table, int off_y, int off_x, vector<vector<vector<int>>>& pieces) {
    vector<vector<int>> temp(6, vector<int>(12)); // 임시 저장, 조각들 최대 길이 6 * 2
    vector<vector<int>> save;                     // 사이즈에 맞춘 저장할 그리드
    int size_y = 0, size_x = 0;                   // save 크기 resize
    queue<coord> q;
    q.push({0, 5}); // 0~5, 0~11 y x
    visited[off_y][off_x] = 1;

    while (!q.empty()) {
        coord now = q.front();
        q.pop();
        temp[now.y][now.x] = 1;

        // 4방향 탐색
        for (int i = 0; i < 4; i++) {
            int next_y = now.y + diry[i];
            int next_x = now.x + dirx[i];
            if (next_y < 0 || next_x < 0 || next_y >= table.size() || next_x >= table.size()) continue;
            if (table[next_y][next_x] == 0) continue;
            if (visited[next_y][next_x] == 1) continue;
            visited[next_y][next_x] = 1;
            temp[next_y][next_x] = 1;
            q.push({next_y, next_x});
        }
    }
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = -1;
    vector<vector<vector<int>>> pieces; // 조각들 저장

    for (int y = 0; y < table.size(); y++) {
        for (int x = 0; x < table.size(); x++) {
            if (table[y][x] == 0) continue;
            table_save(table, y, x, pieces);
        }
    }

    return answer;
}