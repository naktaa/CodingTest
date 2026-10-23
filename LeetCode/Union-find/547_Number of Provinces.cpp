#include <vector>
using namespace std;

class Solution {
    vector<int> parent;

    int find(int now) {
        if (now == parent[now]) return now;
        return parent[now] = find(parent[now]);
    }

    void Union(int a, int b) {
        int roota = find(a);
        int rootb = find(b);
        if (roota == rootb) return;
        parent[rootb] = roota;
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int size = isConnected.size();
        parent.resize(size);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }

        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (isConnected[i][j]) Union(i, j);
            }
        }

        vector<int> visited(200, 0);
        for (int i = 0; i < size; i++) {
            visited[find(i)]++;
        }

        int cnt = 0;
        for (int v : visited) {
            if (v) cnt++;
        }

        return cnt;
    }
};