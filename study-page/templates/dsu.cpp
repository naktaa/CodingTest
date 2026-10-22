#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

vector<int> parent, componentSize;

void initDsu(int N) {
    parent.resize(N);
    iota(parent.begin(), parent.end(), 0);
    componentSize.assign(N, 1);
}

int find(int now) {
    if (parent[now] == now) return now;
    return parent[now] = find(parent[now]);
}

bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (componentSize[a] < componentSize[b]) swap(a, b);
    parent[b] = a;
    componentSize[a] += componentSize[b];
    return true;
}
