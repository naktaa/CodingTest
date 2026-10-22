#include <iostream>
using namespace std;
using ll = long long;

ll gcdValue(ll a, ll b) { // a, b >= 0
    while (b != 0) {
        ll next = a % b;
        a = b;
        b = next;
    }
    return a;
}
