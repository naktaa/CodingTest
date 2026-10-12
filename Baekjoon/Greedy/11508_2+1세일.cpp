#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<int> price;
    int ans = 0;

    cin >> N;
    price.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> price[i];
        ans += price[i];
    }

    sort(price.begin(), price.end(), greater<int>());

    int cnt = price.size() / 3;
    for (int i = 0; i < cnt; i++) {
        ans -= price[3 * i + 2];
    }

    cout << ans << "\n";
}

/*
for (auto d : price) {
    cout << d << " ";
}
*/