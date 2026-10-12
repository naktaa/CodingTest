#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int A, B, C;
    int dat[101] = {0};
    int ans = 0;

    cin >> A >> B >> C;
    for (int i = 0; i < 3; i++) {
        int from, to;
        cin >> from >> to;
        for (int j = from; j < to; j++) {
            dat[j]++;
        }
    }

    for (const auto& cnt : dat) {
        if (!cnt) continue;
        switch (cnt) {
        case 1:
            ans += cnt * A;
            break;
        case 2:
            ans += cnt * B;
            break;
        case 3:
            ans += cnt * C;
            break;
        }
    }

    cout << ans << "\n";
}