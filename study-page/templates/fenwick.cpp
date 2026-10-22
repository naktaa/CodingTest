#include <vector>
using namespace std;
using ll = long long;

int N;
vector<ll> bit;

void initFenwick(int size) {
    N = size;
    bit.assign(N + 1, 0);
}

void add(int idx, ll delta) { // 1 <= idx <= N
    for (int i = idx; i <= N; i += i & -i) bit[i] += delta;
}

ll prefixSum(int idx) { // 0 <= idx <= N
    ll ans = 0;
    for (int i = idx; i > 0; i -= i & -i) ans += bit[i];
    return ans;
}

ll rangeSum(int left, int right) { // 1-based [left, right]
    return prefixSum(right) - prefixSum(left - 1);
}
