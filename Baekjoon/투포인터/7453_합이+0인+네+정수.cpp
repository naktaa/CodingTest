// 백트래킹은 불가능
// 배열마다 하나씩 뽑아서 더한 경우의 수
// 합 배열을 2개씩 묶어서 2개 따로 만들기

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<int> A, B, C, D;
    vector<int> sum1, sum2;
    ll cnt = 0;

    cin >> N;
    sum1.reserve(N * N);
    sum2.reserve(N * N);
    for (int i = 0; i < N; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        D.push_back(d);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum1.push_back(A[i] + B[j]);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum2.push_back(C[i] + D[j]);
        }
    }
    sort(sum1.begin(), sum1.end());
    sort(sum2.begin(), sum2.end());

    // 투포인터로
    int left = 0, right = sum2.size() - 1;
    while (left < sum1.size() && right >= 0) {
        int sum = sum1[left] + sum2[right];
        // cout << "sum = " << sum1[left] << " + " << sum2[right] << " = " << sum << "  |  (left, right): (" << left << ", " << right << ")\n";

        if (sum == 0) {
            int target1 = sum1[left], target2 = sum2[right];
            ll cnt1 = 0, cnt2 = 0;

            for (int i = left; sum1[i] == target1 && i < sum1.size(); i++) {
                cnt1++;
            }
            for (int i = right; sum2[i] == target2 && i >= 0; i--) {
                cnt2++;
            }

            cnt += (cnt1 * cnt2);
            left += cnt1;
            right -= cnt2;
        }
        else if (sum < 0) {
            left++;
        }
        else if (sum > 0) {
            right--;
        }
    }

    cout << cnt << "\n";
}