#include <stack>
#include <vector>
using namespace std;

vector<int> arr, ans;

void nextGreaterDistance() {
    ans.assign(arr.size(), 0);
    stack<int> st;
    for (int i = 0; i < static_cast<int>(arr.size()); i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i - idx;
        }
        st.push(i);
    }
}
