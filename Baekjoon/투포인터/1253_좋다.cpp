#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;


int n;
vector<int> num;
int ans;

int main() {
    cin >> n;
    num.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    sort(num.begin(), num.end());

    for (int i = 0; i < n; i++) {
        int left = 0;
        int right = n - 1;

        while (left < right) {
            if (left == i) {
                left++;
                continue;
            }
            if (right == i) {
                right--;
                continue;
            }

            int sum = num[left] + num[right];

            if (sum == num[i]) {
                ans++;
                break;
            }
            else if (sum < num[i])
                left++;
            else
                right--;
        }
    }

    cout << ans;

    return 0;
}