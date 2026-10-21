#include <algorithm>
#include <array>
#include <functional>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

vector<pair<long long, long long>> jobs;
vector<int> ans;
vector<array<long long, 3>> sortedJobs;

void scheduleJobs() {
    sortedJobs.clear();
    ans.clear();
    for (int i = 0; i < static_cast<int>(jobs.size()); i++) {
        sortedJobs.push_back({jobs[i].first, jobs[i].second, i});
    }
    sort(sortedJobs.begin(), sortedJobs.end());
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;
    int idx = 0;
    int n = jobs.size();
    long long now = 0;
    while (idx < n || !pq.empty()) {
        if (pq.empty()) now = max(now, sortedJobs[idx][0]);
        while (idx < n && sortedJobs[idx][0] <= now) {
            pq.push({sortedJobs[idx][1], static_cast<int>(sortedJobs[idx][2])});
            idx++;
        }
        auto next = pq.top();
        pq.pop();
        now += next.first;
        ans.push_back(next.second);
    }
}
