// i ~ j 까지의 합 구하기
// 1-based

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    vector<int> sum(N + 1, 0); // 0 ~ N 인덱스
    // 누적합 저장
    for (int i = 1; i <= N; i++) {
        int num;
        cin >> num;
        sum[i] = sum[i - 1] + num;
    }
    for (int t = 0; t < M; t++) {
        int i, j;
        cin >> i >> j;
        cout << sum[j] - sum[i - 1] << "\n"; // j까지의 합 - i-1까지의 합
    }
}