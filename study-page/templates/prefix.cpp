#include <vector>
using namespace std;

vector<int> arr;
vector<long long> prefix;

void buildPrefix() {
    int n = arr.size();
    prefix.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
}

long long rangeSum(int left, int right) {
    return prefix[right] - prefix[left]; // [left, right)
}
