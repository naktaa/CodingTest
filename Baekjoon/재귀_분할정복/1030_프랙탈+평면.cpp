// 처음에 1X1 흰색 사각형 하나로 시작
// 시간 지날때마다 NxN개의 크기가 동일한 사각형이 증가
// 나뉜 사각형이 흰색이면 가운데 KxK 만큼 검정색으로 변함
// 입력 s, N, K, R1, R2, C1, C2 -
// 1초마다 8방향으로 똑같은 패턴이 복제되고 중앙은 무조건 검은색으로 채워짐
// 패턴 저장해놓고 (0,0)부터 복제해서 중앙에 검정으로 칠하기
// s초 지날때마다 N^s 만큼 크기의 정사각형
// 2초 이상일때는 s-1초의 패턴만 알면 s초일때 모습 출력 가능
// ------------------------------------------------------------------------
// 분할 정복으로 풀어야함
// 안 그러면 메모리 부족

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int s, N, K, R1, R2, C1, C2; // 시간, 정사각형 크기, 가운데 크기, (R1,C1) ~ (R2,C2)
vector<vector<int>> grid;
vector<vector<int>> grid_temp;
int dif; // k 범위 계산용

void spread(int level) {
    int length = pow(N, level - 1); // 복사되는 프렉탈 정사각형 한 변 길이
    grid.resize(length * N, vector<int>(length * N));

    cout << "grid_temp_before" << "\n";
    cout << "--------------------" << "\n";
    for (int r = 0; r < length; r++) {
        for (int c = 0; c < length; c++) {
            cout << grid_temp[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    // 프랙탈 복제
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int r = 0; r < length; r++) {
                for (int c = 0; c < length; c++) {
                    int dr = i * length + r;
                    int dc = j * length + c;
                    // k범위 안쪽이면 검정
                    if (i >= dif && i < N - dif && j >= dif && j < N - dif) {
                        grid[dr][dc] = 1;
                    }
                    else {
                        grid[dr][dc] = grid_temp[r][c];
                    }
                }
            }
        }
    }

    cout << "check" << level << "\n";
    cout << "\n";
    grid_temp = grid;

    cout << "grid_temp_after" << "\n";
    cout << "--------------------" << "\n";
    for (int r = 0; r < length * N; r++) {
        for (int c = 0; c < length * N; c++) {
            cout << grid_temp[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cin >> s >> N >> K >> R1 >> R2 >> C1 >> C2;
    if (s >= 2) {
        grid.resize(pow(N, s - 1), vector<int>(pow(N, s - 1)));
        grid_temp.resize(pow(N, s - 1), vector<int>(pow(N, s - 1)));
    }
    else {
        grid.resize(N, vector<int>(N));
        grid_temp.resize(N, vector<int>(N));
    }
    dif = (N - K) / 2;

    cout << "\n";
    int t = 1;
    while (t <= s) {
        spread(t);
        t++;
        int len = pow(N, t - 1);
        cout << "grid" << "\n";
        cout << "--------------------" << "\n";
        for (int r = 0; r < len; r++) {
            for (int c = 0; c < len; c++) {
                cout << grid[r][c] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}