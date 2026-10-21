#include <algorithm>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

vector<pair<long long, long long>> intervals;
int ans;

bool cmp(const pair<long long, long long>& now,
         const pair<long long, long long>& next) {
    if (now.second != next.second) return now.second < next.second;
    return now.first < next.first;
}

int maxMeetings() {
    sort(intervals.begin(), intervals.end(), cmp);
    long long last = numeric_limits<long long>::lowest();
    ans = 0;
    for (const auto& now : intervals) {
        if (now.first < last) continue;
        last = now.second;
        ans++;
    }
    return ans;
}
