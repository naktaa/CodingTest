#include <vector>
using namespace std;

int n, m;
vector<int> path;
vector<vector<int>> ans;

void dfs(int start) {
    if (static_cast<int>(path.size()) == m) {
        ans.push_back(path);
        return;
    }
    for (int i = start; i < n; i++) {
        int need = m - path.size();
        if (n - i < need) break;
        path.push_back(i);
        dfs(i + 1);
        path.pop_back();
    }
}

void combinations() {
    path.clear();
    ans.clear();
    dfs(0);
}
