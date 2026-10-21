#include <algorithm>
#include <vector>
using namespace std;

vector<long long> arr, coords;
vector<int> compressed;

void compress() {
    coords = arr;
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    compressed.clear();
    for (long long now : arr) {
        int idx = lower_bound(coords.begin(), coords.end(), now) - coords.begin();
        compressed.push_back(idx);
    }
}
