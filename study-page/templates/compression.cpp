#include <algorithm>
#include <vector>
using namespace std;

vector<int> nums, coords; // 좌표의 절댓값 <= 10^9
vector<int> compressed;

void compress() {
    coords = nums;
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    compressed.clear();
    for (int now : nums) {
        int idx = lower_bound(coords.begin(), coords.end(), now) - coords.begin();
        compressed.push_back(idx);
    }
}
