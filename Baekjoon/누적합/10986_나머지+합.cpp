// 누적합마다 M으로 나눠떨어진 결과를 모아놓고 경우의 수 구하기
// 누적합 배열은 따로 필요없음
/*
1 3 6 7 9
1 0 0 1 0
mod 0 -> 3  --> 1 + 2 + 3 = 6
mod 1 -> 2  -->
mod 2 -> 0
*/

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    ll M;
    ll presum = 0;
    vector<ll> mods;
    ll cnt = 0;

    cin >> N >> M;
    mods.resize(M, 0);
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        presum += n;
        mods[presum % M]++;
    }

    for (int i = 0; i < M; i++) {
        if (i == 0) {
            cnt += (mods[i] * (mods[i] + 1) / 2);
        }
        else {
            if (mods[i] <= 1) continue;
            cnt += ((mods[i] - 1) * mods[i] / 2);
        }
    }

    cout << cnt << "\n";
}