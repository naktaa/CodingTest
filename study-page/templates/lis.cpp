#include <algorithm>
#include <vector>
using namespace std;

vector<int> nums, tails;

int lisLength() {
    tails.clear();
    for (int now : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), now);
        if (it == tails.end()) tails.push_back(now);
        else *it = now;
    }
    int len = tails.size();
    return len;
}
