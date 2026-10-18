// 연속해서 털면 안됨
// 싸이클 구조
// 구간을 설정?
// ---------------------------
// 첫번째집을 터는 경우 안터는 경우로 나눠서 해결 -> 선형으로 만드는게 핵심

#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int solution(vector<int> money) {
    int answer = 0;
    int dp[2][1000001]; // 0 -> 첫번째집 O, 1 -> 첫번째집 X
    memset(dp, 0, sizeof(dp));

    dp[0][0] = money[0];
    dp[0][1] = money[0];
    dp[1][1] = money[1];

    // 첫번째집 O
    for (int i = 2; i < money.size() - 1; i++) {
        dp[0][i] = max(dp[0][i - 1], dp[0][i - 2] + money[i]);
    }

    // 첫번째집 X
    for (int i = 2; i < money.size(); i++) {
        dp[1][i] = max(dp[1][i - 1], dp[1][i - 2] + money[i]);
    }

    answer = max(dp[0][money.size() - 2], dp[1][money.size() - 1]);
    return answer;
}