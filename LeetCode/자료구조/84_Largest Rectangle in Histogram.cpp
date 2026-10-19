/*
N <= 1e5, 0 <= height <= 1e4
단조스택
idx마다 양쪽으로 구하기 -> 왼쪽으로 한번, 오른쪽으로 한번
*/

#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        vector<int> width(len, 1);
        stack<int> st;

        // 오른쪽으로
        for (int i = 0; i < len; i++) {
            while (!st.empty() && heights[st.top()] > heights[i]) {
                int idx = st.top();
                st.pop();
                width[idx] += (i - idx - 1);
            }
            st.push(i);
        }
        while (!st.empty()) {
            int idx = st.top();
            st.pop();
            width[idx] += (len - idx - 1);
        }

        // 왼쪽으로
        for (int i = len - 1; i >= 0; i--) {
            while (!st.empty() && heights[st.top()] > heights[i]) {
                int idx = st.top();
                st.pop();
                width[idx] += (idx - i - 1);
            }
            st.push(i);
        }
        while (!st.empty()) {
            int idx = st.top();
            st.pop();
            width[idx] += idx;
        }

        int MAX = 0;
        for (int i = 0; i < len; i++) {
            MAX = max(MAX, heights[i] * width[i]);
        }

        return MAX;
    }
};