#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int cnt = 0;
    int num = 666;

    while (1) {
        if (to_string(num).find("666") != string::npos) {
            cnt++;
            if (cnt == n) {
                cout << num << '\n';
                break;
            }
        }
        num++;
    }
}