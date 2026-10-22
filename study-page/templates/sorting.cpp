#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int, string>> nums;

bool cmp(const pair<int, string>& now, const pair<int, string>& next) {
    if (now.first != next.first) {
        return now.first > next.first;
    }
    return now.second < next.second;
}

void sortRecords() {
    sort(nums.begin(), nums.end(), cmp);
}
