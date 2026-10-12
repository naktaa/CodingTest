// 비트마스킹은 오래 걸림
// 백트래킹 훨씬 빠름

#include <iostream>
#include <vector>
using namespace std;

int N, S;
vector<int> arr;
int cnt = 0, sum = 0;

void func(int depth) {
    for (int i = depth; i < N; i++) {
        sum += arr[i];
        if (sum == S) cnt++;
        func(i + 1);
        sum -= arr[i];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> S;
    arr.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    func(0);

    // for (int bit = 1; bit <= ((1 << N) - 1); bit++) {
    //     int sum = 0;
    //     for (int i = 0; i < N; i++) {
    //         if (((1 << i) & bit) == 0) continue;
    //         sum += arr[i];
    //     }
    //     if (sum == S) cnt++;
    // }

    cout << cnt << "\n";
}