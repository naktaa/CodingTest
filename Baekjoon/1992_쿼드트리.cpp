// n*n 영역으로 나누어서 0 1 표현
// 1 <= N <= 64  N은 2의 제곱수
// 전체 영역을 4분할 해가며 판별

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int N;
    vector<vector<int>> grid;
    cin >> N;
    grid.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        string temp;
        cin >> temp;
        for (auto n : temp) {
            grid[i].push_back(n - 'a');
        }
    }

    //
}