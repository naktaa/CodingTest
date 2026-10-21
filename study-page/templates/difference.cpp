#include <vector>
using namespace std;

int n;
vector<long long> diff, ans;

void initDifference(int size) {
    n = size;
    diff.assign(n + 1, 0);
    ans.assign(n, 0);
}

void addRange(int left, int right, long long value) {
    diff[left] += value;
    diff[right] -= value; // [left, right)
}

void restore() {
    long long now = 0;
    for (int i = 0; i < n; i++) {
        now += diff[i];
        ans[i] = now;
    }
}
