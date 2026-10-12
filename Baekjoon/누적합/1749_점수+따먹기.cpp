// 누적합 문제
// N x M 그리드
// 일정 구역 숫자들의 합의 최대
// 행마다 누적합 저장하고 행마다 구해서 더하면됨
// ---------------------------------------------------
// 카데인 알고리즘 - 0부터 N-1까지 최대 갱신하면서 진행
// 현재 위치의 값 vs 이전 최대합 + 현재값
// 먼저 M개의 열에 대해 left,right 줄을 정함
// 그 다음 N개의 행에 대해 카데인 알고리즘 적용해서 시간복잡도 줄이기

#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    int N, M; // N x M  |  1 < N, M < 200
    cin >> N >> M;
    vector<vector<int>> grid(N, vector<int>(M)); // 누적합 저장
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            cin >> grid[r][c];
        }
    }

    int ans = -21e8;
    for (int left = 0; left < M; left++) {
        vector<int> sum(N, 0); // N행의 left ~ right 합
        // left ~ M-1 까지 순서대로 sum 갱신하며 카데인 수행
        for (int right = left; right < M; right++) {
            for (int r = 0; r < N; r++) {
                sum[r] += grid[r][right];
            }
            int cur_sum = -21e8; // 현재 위치까지의 부분합의 최대
            int max_sum = -21e8; // 지금까지 최대합
            for (int r = 0; r < N; r++) {
                cur_sum = max(sum[r], cur_sum + sum[r]);
                max_sum = max(cur_sum, max_sum);
            }
            ans = max(ans, max_sum);
        }
    }


    cout << ans << "\n";
}