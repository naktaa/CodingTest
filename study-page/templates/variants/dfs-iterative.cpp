#include <stack>
#include <vector>
using namespace std;

vector<vector<int>> edges;
vector<int> visited, ans;

void traverseIterative(int start) {
    int len = edges.size();
    visited.assign(len, 0);
    ans.clear();
    stack<int> st;
    visited[start] = 1;
    st.push(start);
    while (!st.empty()) {
        int now = st.top();
        st.pop();
        ans.push_back(now);
        int nextLen = edges[now].size();
        for (int i = 0; i < nextLen; i++) {
            int next = edges[now][i];
            if (visited[next]) continue;
            visited[next] = 1;
            st.push(next);
        }
    }
}
