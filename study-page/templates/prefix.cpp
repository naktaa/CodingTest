#include <vector>
using namespace std;
using ll = long long;

vector<int> nums;
vector<ll> prefix;

void buildPrefix() {
    int len = nums.size();
    prefix.assign(len + 1, 0);
    for (int i = 0; i < len; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
}

ll rangeSum(int left, int right) {
    return prefix[right] - prefix[left]; // [left, right)
}
