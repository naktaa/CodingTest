// ------------------------------------------------------------------------------------------------
// 그냥 인접리스트랑 degree로 관리하면서 넣어주는게 더 깔끔함

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <queue>
#include <algorithm>
using namespace std;

struct Work {
    int num = -1, time = 0;    // 작업번호, 작업시간
    unordered_set<int> degree; // 선행작업
};

struct node {
    int num, time;
    bool operator<(node other) const {
        return time > other.time;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // int degree[26][26] = {0};
    // int cost[26] = {0};
    Work works[26];

    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string temp;
        int task = -1, time = 0;

        while (ss >> temp) {
            if (task == -1) {
                task = temp[0] - 'A';
                works[task].num = task;
                continue;
            }
            if (!time) {
                time = stoi(temp);
                works[task].time = time;
                continue;
            }
            for (const auto& c : temp) {
                works[task].degree.insert(c - 'A'); // 위상 차수 넣어주기
            }
        }
    }

    // 초기조건
    int ans = 0;
    priority_queue<node> q;
    for (const auto& w : works) {
        if (w.degree.empty()) q.push({w.num, w.time});
    }

    while (!q.empty()) {
        node now = q.top();
        q.pop();
        ans = max(ans, now.time);
        // cout << now.num << " -> " << now.time << "\n";

        for (auto& w : works) {
            if (w.degree.find(now.num) == w.degree.end()) continue; // 위상차수 없으면 pass
            w.degree.erase(now.num);
            if (w.degree.empty()) q.push({w.num, now.time + works[w.num].time});
        }
    }

    cout << ans << "\n";
}