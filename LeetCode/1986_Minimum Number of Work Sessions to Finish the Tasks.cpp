/*
n <= 14
작업 시간들이 주어지고 세션타임 한번 안에 작업 시간의 합만큼 할 수 있음
최소 세션타임 구하기
그리디?
정렬해서 하면 반례 생김  [7 4 3 8 10], 12
안되면 다음거 찾기
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        sort(tasks.begin(), tasks.end());
        int cnt = 0;

        while (!tasks.empty()) {
            int Time = sessionTime;

            while (!tasks.empty()) {
                bool found = false;

                for (int i = tasks.size() - 1; i >= 0; i--) {
                    if (tasks[i] <= Time) {
                        Time -= tasks[i];
                        tasks.erase(tasks.begin() + i);
                        found = true;
                        break;
                    }
                }

                if (!found) break;
            }

            cnt++;
        }

        return cnt;
    }
};