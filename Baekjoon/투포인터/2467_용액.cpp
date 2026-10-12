// 이분탐색 투포인터
// 오름차순 정렬
// 0과의 차이가 적을수록 좋음
// 만약에 음수 부호가 바뀌면 그 값에서는 최적의 답
// 음수일 때는 left++ 양수일 때는 right--

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<int> acid;    // 용액
    int left = 0, right; // 왼 오 포인터
    int sum;             // 합 계산
    int MIN = 21e8;
    pair<int, int> ans;

    cin >> N;
    right = N - 1;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        acid.push_back(num);
    }

    while (left < right) {
        sum = acid[left] + acid[right];
        if (abs(sum) < MIN) {
            MIN = abs(sum);
            ans.first = left;
            ans.second = right;
        }
        if (sum < 0) {
            left++;
        }
        else if (sum > 0) {
            right--;
        }
        else {
            break;
        }
    }

    cout << acid[ans.first] << " " << acid[ans.second] << "\n";
}