#include <iostream>
#include <stack>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int K;
    stack<ll> money;
    ll sum = 0;

    cin >> K;
    ll now;

    while (K--) {
        cin >> now;
        if (now) {
            sum += now;
            money.push(now);
        }
        else {
            sum -= money.top();
            money.pop();
        }
    }

    cout << sum << "\n";
}