// 최소 2 vs 2
// ================================================
// 비트마스킹으로 접근
// 중복되는 경우의 수는 한쪽에 1번 사람 지정해놓기

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<vector<int>> stat;
    int bit1, bit2;
    int ans = 1e8;

    cin >> N;
    stat.resize(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> stat[i][j];
        }
    }

    for (int mask = 0; mask < ((1 << (N - 1)) - 1); mask++) {
        bit1 = (mask << 1) | 1; // 1번 사람은 고정
        bit2 = ((1 << N) - 1) & ~bit1;
        int sum_start = 0, sum_link = 0;
        vector<int> start, link;
        start.push_back(0);

        for (int i = 1; i < N; i++) {
            if (bit1 & (1 << i))
                start.push_back(i);
            else
                link.push_back(i);
        }

        for (int i = 0; i < start.size() - 1; i++) {
            for (int j = i + 1; j < start.size(); j++) {
                sum_start += (stat[start[i]][start[j]] + stat[start[j]][start[i]]);
            }
        }
        for (int i = 0; i < link.size() - 1; i++) {
            for (int j = i + 1; j < link.size(); j++) {
                sum_link += (stat[link[i]][link[j]] + stat[link[j]][link[i]]);
            }
        }

        ans = min(ans, abs(sum_start - sum_link));
    }

    cout << ans << "\n";
}
