#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

vector<int> nums;
ll target, sum;
int ans;

int minWindowLength() {
    int len = nums.size();
    int left = 0;
    sum = 0;
    ans = len + 1;
    for (int right = 0; right < len; right++) {
        sum += nums[right];
        while (sum >= target) {
            ans = min(ans, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    if (ans == len + 1) ans = 0;
    return ans;
}
