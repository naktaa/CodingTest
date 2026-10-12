// 부 배열은 연속된 수열 --> 누적합인듯
// ===========================================================
// 누적합 배열에서 부분합 저장하고 투포인터 적용
// 중복된 값 생각해서 cnta * cntb 처리 반드시 필요

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T, n, m;
    vector<int> presumA, presumB;
    vector<int> sumA, sumB;
    ll cnt = 0;

    cin >> T;
    cin >> n;
    presumA.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        presumA[i] = presumA[i - 1] + a;
    }
    cin >> m;
    presumB.resize(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        int b;
        cin >> b;
        presumB[i] = presumB[i - 1] + b;
    }

    // A, B의 누적합의 경우의 수 만들기
    sumA.reserve(n * (n + 1) / 2);
    sumB.reserve(m * (m + 1) / 2);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int sum = presumA[j] - presumA[i];
            sumA.push_back(sum);
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j <= m; j++) {
            int sum = presumB[j] - presumB[i];
            sumB.push_back(sum);
        }
    }
    sort(sumA.begin(), sumA.end());
    sort(sumB.begin(), sumB.end());

    // cout << "\nsumA --> ";
    // for (auto a : sumA) {
    //     cout << a << " ";
    // }
    // cout << "\nsumB --> ";
    // for (auto a : sumB) {
    //     cout << a << " ";
    // }
    // cout << "\n";

    int left = 0, right = sumB.size() - 1;
    while (left < sumA.size() && right >= 0) {
        int sum = sumA[left] + sumB[right];
        // cout << "left right sum = " << left << ", " << right << ", " << sum << "\n";

        if (sum == T) {
            int cmpa = sumA[left], cmpb = sumB[right];
            ll cnta = 0, cntb = 0;

            for (int i = left; sumA[i] == cmpa; i++) {
                cnta++;
                if (i == sumA.size() - 1) break;
            }
            for (int i = right; sumB[i] == cmpb; i--) {
                cntb++;
                if (i == 0) break;
            }

            cnt += (cnta * cntb);
            left += cnta;
            right -= cntb;
        }
        else if (sum < T)
            left++;
        else if (sum > T)
            right--;
    }

    cout << cnt << "\n";
}