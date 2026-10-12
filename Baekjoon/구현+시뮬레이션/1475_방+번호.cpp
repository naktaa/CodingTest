#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string N;
    int nums[10] = {0};

    cin >> N;
    for (char n : N) {
        if (n - '0' == 9) {
            nums[n - '3']++; // 9는 6에 더해줌
        }
        else {
            nums[n - '0']++;
        }
    }

    if (nums[6] % 2 == 1) {
        nums[6] = nums[6] / 2 + 1;
    }
    else {
        nums[6] /= 2;
    }
    sort(nums, nums + 10);

    cout << nums[9] << "\n";
}