#include <deque>
#include <vector>
using namespace std;

vector<int> nums, ans;
int K;

void windowMaximum() {
    int len = nums.size();
    ans.clear();
    if (K <= 0 || K > len) return;
    deque<int> dq;
    for (int i = 0; i < len; i++) {
        while (!dq.empty() && dq.front() < i - K + 1) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= K - 1) ans.push_back(nums[dq.front()]);
    }
}
