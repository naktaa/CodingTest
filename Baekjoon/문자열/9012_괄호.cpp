#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        string s;
        cin >> s;

        int balance = 0;
        bool isValid = true;

        for (char c : s) {
            if (c == '(') {
                ++balance;
            }
            else {
                --balance;
            }

            if (balance < 0) {
                isValid = false;
                break;
            }
        }

        if (balance != 0) {
            isValid = false;
        }

        cout << (isValid ? "YES\n" : "NO\n");
    }

    return 0;
}
