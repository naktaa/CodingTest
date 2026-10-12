#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Task {
    int task, time;
    bool operator<(Task other) const {
        return time > other.time;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<int> indegree;
    vector<vector<int>> order;
    vector<int> time;

    cin >> N;
    indegree.resize(N + 1, 0);
    order.resize(N + 1);
    time.resize(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> time[i];
        int M;
        cin >> M;
        indegree[i] += M;
        while (M--) {
            int pre;
            cin >> pre;
            order[pre].push_back(i);
        }
    }

    int ans;
    priority_queue<Task> q;
    for (int i = 1; i <= N; i++) {
        if (!indegree[i]) q.push({i, time[i]});
    }

    while (!q.empty()) {
        Task now = q.top();
        q.pop();
        ans = now.time;

        for (const auto& next : order[now.task]) {
            indegree[next]--;
            if (indegree[next]) continue;
            q.push({next, now.time + time[next]});
        }
    }
    cout << ans << "\n";
}