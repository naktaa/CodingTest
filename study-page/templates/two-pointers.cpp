#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

vector<int> nums;
ll target;

bool hasPair() {
    int len = nums.size();
    sort(nums.begin(), nums.end());
    int left = 0;
    int right = len - 1;
    while (left < right) {
        ll now = 1LL * nums[left] + nums[right];
        if (now == target) return true;
        if (now < target) left++;
        else right--;
    }
    return false;
}
