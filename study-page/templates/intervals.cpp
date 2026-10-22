#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int, int>> intervals, ans;

void mergeIntervals() {
    int len = intervals.size();
    ans.clear();
    if (intervals.empty()) return;
    sort(intervals.begin(), intervals.end());
    int left = intervals[0].first;
    int right = intervals[0].second;
    for (int i = 1; i < len; i++) {
        if (intervals[i].first <= right) {
            right = max(right, intervals[i].second);
        }
        else {
            ans.push_back({left, right});
            left = intervals[i].first;
            right = intervals[i].second;
        }
    }
    ans.push_back({left, right});
}
