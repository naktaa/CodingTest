#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<int> nums;
    cin >> N;

    while (N--) {
        int n;
        cin >> n;
        nums.push_back(n);
    }
    sort(nums.begin(), nums.end());

    for (int num : nums) {
        cout << num << "\n";
    }
}