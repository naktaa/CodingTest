#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    stack<int> nums;
    string com;

    while (N--) {
        cin >> com;
        if (com == "push") {
            int X;
            cin >> X;
            nums.push(X);
        }
        else if (com == "pop") {
            if (nums.empty()) {
                cout << -1 << "\n";
            }
            else {
                cout << nums.top() << "\n";
                nums.pop();
            }
        }
        else if (com == "size") {
            cout << nums.size() << "\n";
        }
        else if (com == "empty") {
            cout << nums.empty() << "\n";
        }
        else if (com == "top") {
            if (nums.empty()) {
                cout << -1 << "\n";
            }
            else {
                cout << nums.top() << "\n";
            }
        }
    }
}