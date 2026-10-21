#include <algorithm>
#include <vector>
using namespace std;

vector<int> arr, tails;

int lisLength() {
    tails.clear();
    for (int now : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), now);
        if (it == tails.end()) tails.push_back(now);
        else *it = now;
    }
    return tails.size();
}
