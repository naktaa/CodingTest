#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    set<string> name;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        if (s == "ENTER") {
            name.clear();
        }
        else {
            if (name.find(s) == name.end()) {
                name.insert(s);
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
