#include <vector>
using namespace std;
using ll = long long;

int N;
vector<ll> diff, ans;

void initDifference(int size) {
    N = size;
    diff.assign(N + 1, 0);
    ans.assign(N, 0);
}

void addRange(int left, int right, ll value) {
    diff[left] += value;
    diff[right] -= value; // [left, right)
}

void restore() {
    ll now = 0;
    for (int i = 0; i < N; i++) {
        now += diff[i];
        ans[i] = now;
    }
}
