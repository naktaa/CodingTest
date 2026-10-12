#include <iostream>
using namespace std;

int N;
int num[101];
int cnt = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;

    while (N--) {
        int n;
        cin >> n;
        if (num[n])
            cnt++;
        else
            num[n]++;
    }

    cout << cnt << "\n";
}