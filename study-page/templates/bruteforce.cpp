#include <vector>
using namespace std;
using ll = long long;

vector<int> nums;
ll target;
int ans;

int countSubsets() {
    int len = nums.size(); // len <= 20
    ans = 0;
    for (int mask = 0; mask < (1 << len); mask++) {
        ll sum = 0;
        for (int i = 0; i < len; i++) {
            if (mask & (1 << i)) sum += nums[i];
        }
        if (sum == target) ans++;
    }
    return ans;
}
