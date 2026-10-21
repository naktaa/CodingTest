#include <vector>
using namespace std;

vector<long long> arr, tree;

void build(int node, int left, int right) {
    if (left == right) {
        tree[node] = arr[left];
        return;
    }
    int mid = left + (right - left) / 2;
    build(node * 2, left, mid);
    build(node * 2 + 1, mid + 1, right);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void initSegment() {
    tree.assign(arr.size() * 4 + 4, 0);
    if (!arr.empty()) build(1, 0, static_cast<int>(arr.size()) - 1);
}

void update(int node, int left, int right, int idx, long long value) {
    if (left == right) {
        tree[node] = value;
        arr[idx] = value;
        return;
    }
    int mid = left + (right - left) / 2;
    if (idx <= mid) update(node * 2, left, mid, idx, value);
    else update(node * 2 + 1, mid + 1, right, idx, value);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long query(int node, int left, int right, int ql, int qr) {
    if (qr < left || right < ql) return 0;
    if (ql <= left && right <= qr) return tree[node];
    int mid = left + (right - left) / 2;
    return query(node * 2, left, mid, ql, qr)
         + query(node * 2 + 1, mid + 1, right, ql, qr);
}
