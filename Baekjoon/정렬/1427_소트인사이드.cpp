#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string N;
    cin >> N;

    vector<int> v;
    for (const auto& c : N) {
        v.push_back(c - '0');
    }

    sort(v.begin(), v.end(), greater<int>());

    for (const auto& a : v) {
        cout << a;
    }
}