#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int p[1000];
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    sort(p, p + n);

    int sum = 0;
    int prefix = 0;
    for (int i = 0; i < n; ++i) {
        prefix += p[i];
        sum += prefix;
    }

    cout << sum << '\n';
    return 0;
}
