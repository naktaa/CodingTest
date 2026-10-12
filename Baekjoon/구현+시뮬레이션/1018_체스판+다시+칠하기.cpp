// 첫째 줄 부터 M - 7 열 N - 7 행까지 구하기

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    cin >> N >> M;
    vector<string> grid; // M x N
    int ans = 1e8;

    for (int i = 0; i < N; i++) {
        string temp;
        cin >> temp;
        grid.push_back(temp);
    }

    vector<vector<int>> B(N - 7, vector<int>(M - 7, 0)); // 검은색
    vector<vector<int>> W(N - 7, vector<int>(M - 7, 0)); // 흰색

    // 검 흰 한번씩
    for (int r = 0; r < N - 7; r++) {
        for (int c = 0; c < M - 7; c++) {
            int idx = 0;
            int sumB = 0;
            int sumW = 0;
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    // 검은색
                    if ((y + x) % 2 == 0 && grid[r + y][c + x] != 'B')
                        sumB++;
                    else if ((y + x) % 2 == 1 && grid[r + y][c + x] != 'W')
                        sumB++;
                    // 흰색
                    if ((y + x) % 2 == 0 && grid[r + y][c + x] != 'W')
                        sumW++;
                    else if ((y + x) % 2 == 1 && grid[r + y][c + x] != 'B')
                        sumW++;
                }
            }
            ans = min(ans, sumB);
            ans = min(ans, sumW);
        }
    }

    cout << ans << "\n";
}