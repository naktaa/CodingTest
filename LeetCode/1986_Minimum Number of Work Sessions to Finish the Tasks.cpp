/*
n <= 14
작업 시간들이 주어지고 세션타임 한번 안에 작업 시간의 합만큼 할 수 있음
최소 세션타임 구하기
그리디?
정렬해서 하면 반례 생김  [7 4 3 8 10], 12
안되면 다음거 찾기
======================================================================
그리디로 하면 시간초과
비트마스킹 dp로 바꿔서 풀기
dp(used, {session, empty})
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    struct task {
        int cnt, emptyTime;
    };
    vector<task> dp;

    void func(vector<int>& tasks, int sessionTime, int visited) {
        for (int i = 0; i < tasks.size(); i++) {
            if (visited & (1 << i)) continue;

            task now = dp[visited];
            int newSession = 0, ncnt = now.cnt, nemptyTime;
            if (now.emptyTime < tasks[i]) newSession = 1;
            if (newSession) {
                ncnt++;
                nemptyTime = sessionTime - tasks[i];
            }
            else {
                nemptyTime = now.emptyTime - tasks[i];
            }

            int nvisited = visited | (1 << i);
            if (ncnt > dp[nvisited].cnt) continue;
            if (ncnt == dp[nvisited].cnt && nemptyTime <= dp[nvisited].emptyTime) continue;

            dp[nvisited] = {ncnt, nemptyTime};
            func(tasks, sessionTime, nvisited);
        }
    }

public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        dp.assign(1 << tasks.size(), {15, sessionTime});
        dp[0] = {1, sessionTime};
        func(tasks, sessionTime, 0);
        return dp[(1 << tasks.size()) - 1].cnt;
    }
};