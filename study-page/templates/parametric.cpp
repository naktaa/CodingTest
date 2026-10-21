#include <algorithm>
#include <vector>
using namespace std;

vector<long long> lengths;
long long need;

bool can(long long size) {
    long long cnt = 0;
    for (long long now : lengths) {
        cnt += now / size;
        if (cnt >= need) return true;
    }
    return false;
}

long long maxLength() {
    if (lengths.empty()) return 0;
    long long left = 1;
    long long right = *max_element(lengths.begin(), lengths.end());
    long long ans = 0;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (can(mid)) {
            ans = mid;
            left = mid + 1;
        }
        else right = mid - 1;
    }
    return ans;
}
