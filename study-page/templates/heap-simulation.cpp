#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

struct node {
    int start, cost;
    int idx = 0;

    bool operator<(const node& next) const {
        if (cost != next.cost) return cost > next.cost;
        return idx > next.idx;
    }
};

vector<node> jobs, sortedJobs; // 입력은 {도착, 처리}, idx는 함수에서 채움
vector<int> ans;

bool cmp(const node& now, const node& next) {
    if (now.start != next.start) return now.start < next.start;
    return now.idx < next.idx;
}

void scheduleJobs() {
    int len = jobs.size();
    sortedJobs.clear();
    ans.clear();
    for (int i = 0; i < len; i++) {
        sortedJobs.push_back({jobs[i].start, jobs[i].cost, i});
    }
    sort(sortedJobs.begin(), sortedJobs.end(), cmp);
    priority_queue<node> pq;
    int idx = 0;
    ll now = 0;
    while (idx < len || !pq.empty()) {
        if (pq.empty() && now < sortedJobs[idx].start) now = sortedJobs[idx].start;
        while (idx < len && sortedJobs[idx].start <= now) {
            pq.push(sortedJobs[idx]);
            idx++;
        }
        node next = pq.top();
        pq.pop();
        now += next.cost;
        ans.push_back(next.idx);
    }
}
