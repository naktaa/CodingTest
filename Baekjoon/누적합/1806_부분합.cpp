/*
누적합?
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, S;
    vector<int> presum;
    int left = 0, right = 1;
    int MIN = 1e8;

    cin >> N >> S;
    presum.resize(N + 1, 0); // 1-based index
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        presum[i] = presum[i - 1] + n;
    }

    // right가 수열의 길이를 넘거나 MIN이 1일 때 (left == right)
    while (right <= N && left != right) {
        int cursum = presum[right] - presum[left]; // 부분합
        // cout << "left = " << left << ", right = " << right << ", sum = " << cursum << " --> MIN = " << MIN << "\n";

        if (cursum < S) {
            right++;
            continue;
        }
        else {
            MIN = min(MIN, right - left);
            left++;
        }
    }
    if (!left) MIN = 0;

    cout << MIN << "\n";
}