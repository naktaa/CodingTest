/*
배낭 dp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, W; // 1~1000, 1~10000
    vector<int> dp;

    cin >> N >> W;
    dp.assign(W + 1, -1);
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        int w, v;
        cin >> w >> v;
        for (int j = w; j <= W; j++) {
            if (dp[j - w] == -1) continue;
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }

    // sort(dp.begin(), dp.end());
    // cout << dp.back();
    cout << *max_element(dp.begin(), dp.end());
}

/*
4 14
2 40
5 110
10 200
3 50
*/