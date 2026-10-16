/*
k개의 부분수열로 나눴을 때 수열들의 합을 동일하게 만들 수 있는지
1 <= k <= n <= 16,  nums[i] <= 1e4
연속하진 않아도 됨
비트마스킹?
재귀로 구해보기
어떻게 k개의 부분집합으로 쪼갤지 생각 -> 쉽지않음
===============================================================
dfs로 비트마스킹 하면서 sum 관리하면됨
메모이제이션도 필요 중복 조합이 많음
*/

#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

class Solution {
    float avg;
    vector<int> result;

    bool func(vector<int>& nums, int k, int cnt, int mask, int sum) {
        if (cnt == k) return true;

        for (int i = 0; i < nums.size(); i++) {
            if (mask & (1 << i)) continue;

            int nsum = sum + nums[i];
            int nmask = mask | (1 << i);
            if (result[nmask]) continue;

            if (nsum > avg) {
                continue;
            }
            else if (nsum == avg) {
                if (func(nums, k, cnt + 1, nmask, 0)) return true;
            }
            else {
                if (func(nums, k, cnt, nmask, nsum)) return true;
            }
        }

        result[mask] = 1;
        return false;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) return false;

        avg = total / k;
        result.assign(1 << nums.size(), 0);

        return func(nums, k, 0, 0, 0);
    }
};