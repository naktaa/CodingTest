// 굳이 presum 만들지 않고 포인터 둘 다 옮겨져도 가능

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, X;
    vector<int> nums;

    cin >> N;
    nums.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }
    cin >> X;
    sort(nums.begin(), nums.end());

    // 투포인터
    int left = 0, right = N - 1;
    int sum = 0, presum = 1e8;
    int cnt = 0;

    while (left < right) {
        sum = nums[left] + nums[right];
        // cout << "sum = " << nums[left] << " + " << nums[right] << " = " << sum << "\n";

        if (sum == X) {
            cnt++;
            if (presum > sum) {
                right--;
            }
            else
                left++;
        }
        else if (sum < X) {
            left++;
        }
        else if (sum > X) {
            right--;
        }
        presum = sum;
    }

    cout << cnt << "\n";
}