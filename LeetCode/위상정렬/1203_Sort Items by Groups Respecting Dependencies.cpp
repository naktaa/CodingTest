/*
n <= 3e4
위상정렬인데 그룹에 묶여있음
그룹의 차수 확인 필요
선행 작업이 같은 그룹에 있는지 다른 그룹에 있는지 고려해야됨
같은 그룹 넣을 때 다 확인하면 중복되니 한번만 할 수 있게
===============================================================
위상정렬을 2번 사용해야함
그룹 우선수위 -> 작업 우선순위
그룹의 순서가 정렬되면 다른 그룹의 작업 순서도 보장
*/

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        vector<int> groupId = group;
        int groupcnt = m;
        for (int i = 0; i < n; i++) {
            if (group[i] != -1) continue;
            groupId[i] = groupcnt++;
        }

        vector<vector<int>> taskEdges(n);
        vector<int> taskIndegree(n, 0);
        vector<vector<int>> groupEdges(groupcnt);
        vector<int> groupinDegree(groupcnt, 0);
        vector<int> grouporder;
        vector<vector<int>> sortedTask(groupcnt);

        for (int i = 0; i < n; i++) {
            for (int prev : beforeItems[i]) {
                if (groupId[prev] == groupId[i]) {
                    taskEdges[prev].push_back(i);
                    taskIndegree[i]++;
                }
                else {
                    groupEdges[groupId[prev]].push_back(groupId[i]);
                    groupinDegree[groupId[i]]++;
                }
            }
        }

        queue<int> q;

        // group 위상정렬
        for (int i = 0; i < groupcnt; i++) {
            if (groupinDegree[i]) continue;
            q.push(i);
        }

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            grouporder.push_back(now);

            for (const int& next : groupEdges[now]) {
                groupinDegree[next]--;
                if (groupinDegree[next]) continue;
                q.push(next);
            }
        }
        if (grouporder.size() != groupcnt) return {};

        // task 위상정렬
        int taskcnt = 0;
        for (int i = 0; i < n; i++) {
            if (taskIndegree[i]) continue;
            q.push(i);
        }

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            sortedTask[groupId[now]].push_back(now);
            taskcnt++;

            for (const int& next : taskEdges[now]) {
                taskIndegree[next]--;
                if (taskIndegree[next]) continue;
                q.push(next);
            }
        }
        if (taskcnt != n) return {};

        vector<int> ans = {};
        for (auto& order : grouporder) {
            for (const auto& task : sortedTask[order]) {
                ans.push_back(task);
            }
        }

        return ans;
    }
};