/*
N <= 1e5, num <= 1e4, target <= 1e9
합이 target을 넘는 최소길이
현재 sum 확인
-> target 이상이면 MIN 기록하고 left++, 이하면 right++;
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int len = nums.size();
        int left = 0, right = 0, sum = 0;
        int MIN = 1e8;

        while (right < len) {
            sum += nums[right++];

            while (sum >= target) {
                MIN = min(MIN, right - left);
                sum -= nums[left++];
            }
        }

        MIN = (MIN == 1e8) ? 0 : MIN;
        return MIN;
    }
};