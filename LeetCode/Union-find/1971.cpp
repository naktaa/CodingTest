#include <vector>
using namespace std;

class Solution {
    vector<int> parent;

    int find(int now) {
        if (now == parent[now]) return now;
        return parent[now] = find(parent[now]);
    }

    void unite(int a, int b) {
        int roota = find(a);
        int rootb = find(b);
        if (roota == rootb) return;
        parent[rootb] = roota;
    }

public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        for (const auto& edge : edges) {
            unite(edge[0], edge[1]);
        }

        return (find(source) == find(destination) ? true : false);
    }
};