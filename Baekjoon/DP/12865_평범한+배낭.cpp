//   | 0 1 2 3 4 5 6 7
// --------------------
// 0 | 0 0 0 0 0 0 0 0
// 1 | 0 0 0 0 13 13 13 13
// 2 |
// 3 |
// 4 |

/*
4 7
6 13
4 8
3 6
5 12
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct bag {
    int W, V; // 무게, 가치
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    int N, K; // 물품의 수, 최대 중량
    vector<bag> BAG;
    vector<vector<int>> dp;
    int ans;

    cin >> N >> K;
    BAG.resize(N + 1);
    dp.resize(N + 1, vector<int>(K + 1, 0));
    for (int i = 1; i <= N; i++) {
        int w, v;
        cin >> w >> v;
        BAG[i] = {w, v};
    }

    for (int i = 1; i <= N; i++) {
        for (int w = 0; w <= K; w++) {
            if (w < BAG[i].W) {
                dp[i][w] = dp[i - 1][w];
            }
            else {
                dp[i][w] = max(BAG[i].V + dp[i - 1][w - BAG[i].W], dp[i - 1][w]);
            }
        }
    }

    // for (int i = 0; i <= N; i++) {
    //     for (int j = 0; j <= K; j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    cout << dp[N][K] << "\n";
}