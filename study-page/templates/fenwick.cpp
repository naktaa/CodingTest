#include <vector>
using namespace std;

int n;
vector<long long> bit;

void initFenwick(int size) {
    n = size;
    bit.assign(n + 1, 0);
}

void add(int idx, long long delta) { // 1 <= idx <= n
    for (int i = idx; i <= n; i += i & -i) bit[i] += delta;
}

long long prefixSum(int idx) { // 0 <= idx <= n
    long long ans = 0;
    for (int i = idx; i > 0; i -= i & -i) ans += bit[i];
    return ans;
}

long long rangeSum(int left, int right) { // 1-based [left, right]
    return prefixSum(right) - prefixSum(left - 1);
}
