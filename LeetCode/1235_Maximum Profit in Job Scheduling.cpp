/*
dp 느낌
job length <= 5 * 10e4
Time <= 10e9
profit <= 10e4
end time 정렬하고 start time 정렬
구간별로 end Time 기준으로 dp
시간초과남
====================================================================================
작업 종료 시간을 정렬하고 순서대로 dp하면 모든 시간에 대해 계산할 필요 X
dp[i] = i번째 작업까지 진행했을 때 최대 이득
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    struct job {
        int start, end, profit;
    };
    static bool cmp(job a, job b) {
        if (a.end != b.end) return a.end < b.end;
        return a.start < b.start;
    }

    vector<job> jobs;
    vector<int> dp;

public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int size = startTime.size();
        jobs.resize(size);
        dp.resize(size, 0);
        for (int i = 0; i < size; i++) {
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        }
        sort(jobs.begin(), jobs.end(), cmp);

        int last = jobs[0].end;
        dp[0] = jobs[0].profit;

        for (int i = 1; i < size; i++) {
            int nprofit;
            if (jobs[i].start >= last) {
                nprofit = dp[i - 1] + jobs[i].profit;
            }
            else {
                nprofit = jobs[i].profit;
            }
        }

        return dp[size - 1];
    }
};