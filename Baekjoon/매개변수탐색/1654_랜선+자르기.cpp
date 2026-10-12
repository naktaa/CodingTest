// 정렬하고 파라메트릭 서치
// ------------------------------------------------------------------------
// 값을 찾는 이분탐색일 때는 left를 1로 두기

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K; // 만들 랜선 수, 가지고 있는 랜선 수
    vector<ll> cable;
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
        ll len;
        cin >> len;
        cable.push_back(len);
    }

    sort(cable.begin(), cable.end());
    ll left = 1, right = cable[K - 1];
    ll mid;

    while (left <= right) {
        mid = (left + right) / 2;
        ll cnt = 0;

        for (const auto& len : cable) {
            cnt += (len / mid);
        }
        // 많이 만들 수 있으면 길이를 더 늘림
        if (cnt >= N) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    cout << right << "\n";
}