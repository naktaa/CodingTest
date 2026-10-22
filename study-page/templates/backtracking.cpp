#include <vector>
using namespace std;

int N, M;
vector<int> path;
vector<vector<int>> ans;

void dfs(int start) {
    int len = path.size();
    if (len == M) {
        ans.push_back(path);
        return;
    }
    for (int i = start; i < N; i++) {
        int need = M - len;
        if (N - i < need) break;
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
