/*
N <= 1000, 1 <= K <= 50
k개로 나눠서 나눈 배열의 합의 최대가 최소가 되도록
배열에서 연속된 서브배열로 나눈다 -> 누적합?
N - 1 개 중에서 K - 1 개 선택
백트래킹? 하면서 MAX 값 넘으면 break 하면서 가지치기
================================================================================
백트래킹 하면 무조건 시간초과
파라메트릭 서치
*/

#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int left = *max_element(nums.begin(), nums.end());
        int right = accumulate(nums.begin(), nums.end(), 0);
        int ans;

        while (left <= right) {
            int mid = (left + right) / 2;
            int sum = 0, cnt = 1;

            for (int& num : nums) {
                if (sum + num > mid) {
                    sum = 0;
                    cnt++;
                }
                sum += num;
            }

            if (cnt > k) {
                left = mid + 1;
            }
            else {
                ans = mid;
                right = mid - 1;
            }
        }

        return ans;
    }
};