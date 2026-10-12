// 하루에 과제 하나
// 뒤에서부터 진행
// 그날 마감

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<vector<int>> homework(1001);
    priority_queue<int> pq;
    int end = 0;
    int ans = 0;

    cin >> N;
    while (N--) {
        int d, w;
        cin >> d >> w;
        end = max(end, d);
        homework[d].push_back(w);
    }

    while (end--) {
        for (const auto& score : homework[end + 1]) {
            pq.push(score);
        }
        if (!pq.empty()) {
            int now = pq.top();
            pq.pop();
            ans += now;
            // cout << now << " ";
        }
    }

    cout << ans << "\n";
}