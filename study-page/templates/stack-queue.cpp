#include <stack>
#include <string>
using namespace std;

string s;
stack<char> st;

bool validParentheses() {
    st = stack<char>();
    for (char now : s) {
        if (now == '(') {
            st.push(now);
        }
        else {
            if (st.empty()) return false;
            st.pop();
        }
    }
    return st.empty();
}
