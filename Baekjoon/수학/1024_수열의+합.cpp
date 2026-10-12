#include <iostream>
using namespace std;

int main() {
    int N, L;
    cin >> N >> L;

    while (L <= 100) {
        // 수열의 합 공식: N = L*x + L*(L-1)/2
        // x = (N - L*(L-1)/2) / L
        long long sum = (long long)L * (L - 1) / 2;

        if ((N - sum) % L == 0) { // 나누어떨어지는지 확인
            long long start = (N - sum) / L;

            if (start >= 0) { // 음수가 아닌 경우
                for (int i = 0; i < L; i++) {
                    cout << start + i << " ";
                }
                return 0;
            }
        }
        L++;
    }

    cout << -1;
    return 0;
}