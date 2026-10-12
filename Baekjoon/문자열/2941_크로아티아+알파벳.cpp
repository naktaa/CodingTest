#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;

    int count = 0;
    for (size_t i = 0; i < s.size();) {
        if (i + 2 < s.size() && s[i] == 'd' && s[i + 1] == 'z' && s[i + 2] == '=') {
            count++;
            i += 3;
            continue;
        }

        if (i + 1 < s.size()) {
            string two = s.substr(i, 2);
            if (two == "c=" || two == "c-" || two == "d-" || two == "lj" || two == "nj" ||
                two == "s=" || two == "z=") {
                count++;
                i += 2;
                continue;
            }
        }

        count++;
        i += 1;
    }

    cout << count << '\n';
    return 0;
}
