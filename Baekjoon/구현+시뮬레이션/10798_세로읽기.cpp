#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<string> words(5);
    vector<int> size(5);
    int MAX = -1;

    for (int i = 0; i < 5; i++) {
        cin >> words[i];
        size[i] = words[i].length();
        MAX = max(MAX, size[i]);
    }

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < 5; j++) {
            if (size[j] <= i) continue;
            cout << words[j][i];
        }
    }
}