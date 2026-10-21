#include <algorithm>
#include <vector>
using namespace std;

vector<int> arr;
long long target;

bool hasPair() {
    sort(arr.begin(), arr.end());
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;
    while (left < right) {
        long long now = 1LL * arr[left] + arr[right];
        if (now == target) return true;
        if (now < target) left++;
        else right--;
    }
    return false;
}
