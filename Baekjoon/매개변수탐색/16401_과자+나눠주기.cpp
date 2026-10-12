// 하나하나 잘라가며 최대 길이로 조카 수마다 나눠주기
// 파라메트릭 서치
// ==================================================================================================
// 파라메트릭 서치 할 때 left = 1 시작, 출력은 right로
// 처음에 vector size 설정하는게 더 메모리 적게 먹음
// sort보다 max_element 써서 max값만 뽑으면 더 빠름

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int M, N; // 조카 수, 과자 수
    vector<int> snack;

    cin >> M >> N;
    snack.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> snack[i];
    }

    // sort(snack.begin(), snack.end(), greater<>());
    int left = 1, right = *max_element(snack.begin(), snack.end());
    int mid = 0;
    bool flag = false;

    while (left <= right) {
        mid = (left + right) / 2;
        int cnt = 0;

        for (const int& len : snack) {
            cnt += len / mid;
        }

        // cout << "left = " << left << ", right = " << right << " --> mid = " << mid << ", cnt = " << cnt << "\n";
        if (cnt >= M) {
            flag = true;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (flag)
        cout << right << "\n";
    else
        cout << 0 << "\n";
}
