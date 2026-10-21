#include <vector>
using namespace std;

vector<int> arr;
long long target, ans;

long long countSubsets() {
    int n = arr.size(); // n <= 20
    ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) sum += arr[i];
        }
        if (sum == target) ans++;
    }
    return ans;
}
