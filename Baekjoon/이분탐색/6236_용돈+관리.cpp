#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    int n, m;
    vector<int> money;
    int k = 0;
    int ans = 0;
    int left = 0;
    int right = 0;

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        left = max(temp, left);
        right += temp;
        money.push_back(temp);
    }

    while (left <= right) {
        int cnt = 1;
        int mid = (left + right) / 2;
        int cur = mid;
        for (int i = 0; i < n; i++) {
            if (money[i] <= cur)
                cur -= money[i];
            else {
                cur = mid;
                cur -= money[i];
                cnt++;
            }
        }
        if (cnt <= m)
            right = mid - 1;
        else
            left = mid + 1;
        ans = mid;
    }


    cout << ans;
    return 0;
}