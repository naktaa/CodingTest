#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;

vector<int> lengths; // 원소 수 <= 200000, 각 길이 0~10^9
int need; // 1~10^9

bool can(int size) {
    ll cnt = 0;
    for (int now : lengths) {
        cnt += now / size;
        if (cnt >= need) return true;
    }
    return false;
}

int maxLength() {
    if (lengths.empty()) return 0;
    int left = 1;
    int right = *max_element(lengths.begin(), lengths.end());
    int ans = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (can(mid)) {
            ans = mid;
            left = mid + 1;
        }
        else right = mid - 1;
    }
    return ans;
}
