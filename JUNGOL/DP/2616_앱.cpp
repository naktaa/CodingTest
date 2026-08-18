/*
하나씩만 사용 가능, 배낭 X
메모이제이션 냄새
0-1 배낭 문제, i번째 이전까지 사용한 메모리들을 검사
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1e9;

int main() {
    int N, M;
    vector<int> A, Cost;
    int sum = 0;

    cin >> N >> M;
    A.resize(N);
    Cost.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> Cost[i];
        sum += Cost[i];
    }

    vector<vector<int>> dp(N + 1, vector<int>(sum + 1, -1));
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        for (int c = 0; c <= sum; c++) {
            if (dp[i - 1][c] == -1) continue;
            // i번째 앱을 종료하지 않는 경우
            dp[i][c] = max(dp[i][c], dp[i - 1][c]);

            // i번째 앱을 종료하는 경우
            int nc = c + Cost[i - 1];
            if (nc > sum) continue;
            dp[i][nc] = max(dp[i][nc], dp[i - 1][c] + A[i - 1]);
        }
    }

    int ans = 0;
    for (int c = 0; c <= sum; c++) {
        if (dp[N][c] < M) continue;
        ans = c;
        break;
    }
    cout << ans << "\n";
}

/*
5 60
30 10 20 35 40
3 0 3 5 4
*/