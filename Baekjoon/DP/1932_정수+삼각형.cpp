#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n; // 삼각형의 크기
    vector<vector<int>> triangle;
    int dp[500][500] = {0};
    int ans = -1;

    cin >> n;
    triangle.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i + 1; j++) {
            int num;
            cin >> num;
            triangle[i].push_back(num);
        }
    }

    // dp 시작
    dp[0][0] = triangle[0][0];

    if (n == 1) {
        ans = triangle[0][0];
    }
    else if (n == 2) {
        ans = max(dp[0][0] + triangle[1][0], dp[0][0] + triangle[1][1]);
    }
    else {
        // 위 층의 왼 오 2개와 더한걸 비교
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i + 1; j++) {
                // 맨 끝 양쪽 처리
                if (j == 0 || j == i) {
                    dp[i][j] = (j == 0) ? dp[i - 1][j] + triangle[i][j] : dp[i - 1][j - 1] + triangle[i][j];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j - 1] + triangle[i][j], dp[i - 1][j] + triangle[i][j]);
                }
                ans = max(ans, dp[i][j]);
            }
        }
    }

    cout << ans << "\n";
}