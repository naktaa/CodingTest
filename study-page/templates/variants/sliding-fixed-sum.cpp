#include <vector>
using namespace std;
using ll = long long;

vector<int> nums;
int K;
ll sum, ans;

ll maxWindowSum() {
    int len = nums.size();
    sum = 0;
    ans = 0;
    if (K <= 0 || K > len) return 0;
    for (int right = 0; right < len; right++) {
        sum += nums[right];
        if (right >= K) sum -= nums[right - K];
        if (right >= K - 1) {
            if (right == K - 1 || sum > ans) ans = sum;
        }
    }
    return ans;
}
