#include <stack>
#include <vector>
using namespace std;

vector<int> nums, ans;

void nextGreaterDistance() {
    int len = nums.size();
    ans.assign(len, 0);
    stack<int> st;
    for (int i = 0; i < len; i++) {
        while (!st.empty() && nums[st.top()] < nums[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i - idx;
        }
        st.push(i);
    }
}
