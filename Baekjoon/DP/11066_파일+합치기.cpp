#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;


int dp[501][501]; // left ~ right 까지 dp
int sum[501];     // 누적합 저장
int k;

void init() {
    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));
}
void input() {
    cin >> k;
}
void solution() {
    vector<int> file(k + 1);

    for (int i = 1; i <= k; i++) {
        cin >> file[i];
        sum[i] = sum[i - 1] + file[i];
    }

    // 2부터 k까지 길이 늘려가면서 dp 시작
    for (int len = 2; len <= k; len++) {
        // 시작점 설정
        for (int start = 1; start <= k - len + 1; start++) {
            int end = start + len - 1;
            dp[start][end] = 21e8; // 초기값 최대로 설정
            // start, end 사이 구간 설정
            for (int mid = start; mid < end; mid++) {
                int cost = dp[start][mid] + dp[mid + 1][end] + sum[end] - sum[start - 1];
                dp[start][end] = min(dp[start][end], cost);
            }
        }
    }
}
int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();
        input();
        solution();
        cout << dp[1][k] << "\n";
    }
    return 0;
}