/*
N <= 1e5, -1e4 <= num <= 1e4
연속된 k개 nums 중 MAX
매번 k개 방문하면 최대 1e10
================================================
단조 덱
i를 윈도우의 끝 인덱스로 사용하면서 진행
front()가 가장 큰 원소의 idx
새로 원소 추가할때마다 기존 front 지우고 deque에 있는 원소보다 작을때까지 pop_back
*/

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();
        vector<int> ans;
        deque<int> dq;

        for (int i = 0; i < len; i++) {
            if (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();

            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);
            if (i < k - 1) continue;
            ans.push_back(nums[dq.front()]);
        }

        return ans;
    }
};