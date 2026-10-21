#include <algorithm>
#include <array>
#include <numeric>
#include <vector>
using namespace std;

int n, cnt;
long long ans;
vector<array<long long, 3>> edges; // weight, from, to
vector<int> parent, componentSize;

int find(int now) {
    if (parent[now] == now) return now;
    return parent[now] = find(parent[now]);
}

bool kruskal() { // n >= 1
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    componentSize.assign(n, 1);
    sort(edges.begin(), edges.end());
    ans = 0;
    cnt = 0;
    for (const auto& edge : edges) {
        int a = find(static_cast<int>(edge[1]));
        int b = find(static_cast<int>(edge[2]));
        if (a == b) continue;
        if (componentSize[a] < componentSize[b]) swap(a, b);
        parent[b] = a;
        componentSize[a] += componentSize[b];
        ans += edge[0];
        cnt++;
    }
    return cnt == n - 1;
}
