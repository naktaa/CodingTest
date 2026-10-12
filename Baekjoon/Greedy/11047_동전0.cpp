#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    stack<int> coin;

    cin >> N >> K;
    while (N--) {
        int cost;
        cin >> cost;
        coin.push(cost);
    }

    int ans = 0;
    while (K) {
        // cout << K << " ";
        ans += K / coin.top();
        K %= coin.top();
        coin.pop();
    }

    cout << ans << "\n";
}