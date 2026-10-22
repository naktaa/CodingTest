#include <functional>
#include <queue>
#include <vector>
using namespace std;

vector<int> nums, ans;
priority_queue<int, vector<int>, greater<int>> pq;

void extractSorted() {
    pq = priority_queue<int, vector<int>, greater<int>>();
    ans.clear();
    for (int now : nums) pq.push(now);
    while (!pq.empty()) {
        ans.push_back(pq.top());
        pq.pop();
    }
}
