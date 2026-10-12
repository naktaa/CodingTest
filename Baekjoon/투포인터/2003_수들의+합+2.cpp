// N개의 수열
// i ~ j 의 합이 M이 되는 경우의 수
// 왼쪽부터 시작해서 작으면 right++, 크면 left++
// 누적합 이용해서 부분합 만들기

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> presum(N + 1, 0); // 누적합
    for (int i = 1; i < N + 1; i++) {
        int num;
        cin >> num;
        presum[i] = presum[i - 1] + num;
    }

    int ans = 0;
    int left = 0;
    int right = 1;
    while (1) {
        int sum = presum[right] - presum[left];
        if (sum == M) {
            ans++;
            right++;
            if (right == N + 1) break;
        }
        else if (sum < M) {
            right++;
            if (right == N + 1) break; // 범위 안벗어나게
        }
        else if (sum > M) {
            left++;
        }
    }

    cout << ans << "\n";
}