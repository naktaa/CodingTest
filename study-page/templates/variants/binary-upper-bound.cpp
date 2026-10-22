#include <vector>
using namespace std;

vector<int> nums;

int upperIndex(int x) {
    int len = nums.size();
    int left = 0;
    int right = len;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= x) left = mid + 1;
        else right = mid;
    }
    return left;
}
