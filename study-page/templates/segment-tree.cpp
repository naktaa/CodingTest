#include <vector>
using namespace std;
using ll = long long;

vector<int> nums;
vector<ll> tree;

void build(int node, int left, int right) {
    if (left == right) {
        tree[node] = nums[left];
        return;
    }
    int mid = left + (right - left) / 2;
    build(node * 2, left, mid);
    build(node * 2 + 1, mid + 1, right);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void initSegment() {
    int len = nums.size();
    tree.assign(len * 4 + 4, 0);
    if (len > 0) build(1, 0, len - 1);
}

void update(int node, int left, int right, int idx, int value) {
    if (left == right) {
        tree[node] = value;
        nums[idx] = value;
        return;
    }
    int mid = left + (right - left) / 2;
    if (idx <= mid) update(node * 2, left, mid, idx, value);
    else update(node * 2 + 1, mid + 1, right, idx, value);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int left, int right, int ql, int qr) {
    if (qr < left || right < ql) return 0;
    if (ql <= left && right <= qr) return tree[node];
    int mid = left + (right - left) / 2;
    return query(node * 2, left, mid, ql, qr)
        + query(node * 2 + 1, mid + 1, right, ql, qr);
}
