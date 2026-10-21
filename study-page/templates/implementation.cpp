#include <string>
using namespace std;

string s;
int ans;

int countGroups() {
    ans = 0;
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        if (i == 0 || s[i] != s[i - 1]) {
            ans++;
        }
    }
    return ans;
}
