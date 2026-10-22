#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;

struct edge {
    int weight, from, to;
};

int N, cnt;
ll ans;
vector<edge> edges;
vector<int> parent, componentSize;

bool cmp(const edge& now, const edge& next) {
    return now.weight < next.weight;
}

int find(int now) {
    if (parent[now] == now) return now;
    return parent[now] = find(parent[now]);
}

bool kruskal() { // 1 <= N <= 200000, |weight| <= 10^9
    parent.resize(N);
    iota(parent.begin(), parent.end(), 0);
    componentSize.assign(N, 1);
    sort(edges.begin(), edges.end(), cmp);
    ans = 0;
    cnt = 0;
    for (edge now : edges) {
        int a = find(now.from);
        int b = find(now.to);
        if (a == b) continue;
        if (componentSize[a] < componentSize[b]) swap(a, b);
        parent[b] = a;
        componentSize[a] += componentSize[b];
        ans += now.weight;
        cnt++;
    }
    return cnt == N - 1;
}
