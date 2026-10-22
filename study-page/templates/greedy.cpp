#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int, int>> intervals; // -10^9 <= 시작 < 종료 <= 10^9
int ans;

bool cmp(const pair<int, int>& now, const pair<int, int>& next) {
    if (now.second != next.second) return now.second < next.second;
    return now.first < next.first;
}

int maxMeetings() {
    sort(intervals.begin(), intervals.end(), cmp);
    int last = -1'000'000'001; // 가능한 시작 시각보다 작음
    ans = 0;
    for (const auto& now : intervals) {
        if (now.first < last) continue;
        last = now.second;
        ans++;
    }
    return ans;
}
