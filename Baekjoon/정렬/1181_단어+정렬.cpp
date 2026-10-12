// set의 cmp 함수 만드는법
// struct cmp { bool operator()(a,b) const}

#include <iostream>
#include <string>
#include <set>
using namespace std;

struct cmp {
    bool operator()(string a, string b) const {
        if (a.length() != b.length()) return a.length() < b.length();
        return a < b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    set<string, cmp> S;

    cin >> N;
    while (N--) {
        string temp;
        cin >> temp;
        S.insert(temp);
    }

    // cout << "\n";
    for (auto s : S) {
        cout << s << "\n";
    }
}