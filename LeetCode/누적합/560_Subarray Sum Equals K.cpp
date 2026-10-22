/*
N <= 2e4, -1000 <= num <= 1000
합이 k인 연속된 부분배열의 수
누적합 구하면서 구할때마다 map에 뺏을때 k가 되는 값이 있는지 확인?
*/

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int size = nums.size();

        vector<int> presum(size + 1, 0);
        unordered_map<int, int> freq;
        freq[0]++;
        int cntSubarray = 0;

        for (int i = 0; i < size; i++) {
            presum[i + 1] = presum[i] + nums[i];
            int target = presum[i + 1] - k;
            if (freq.find(target) != freq.end()) cntSubarray += freq[target];
            freq[presum[i + 1]]++;
        }

        return cntSubarray;
    }
};