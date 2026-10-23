#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> m;
        m[0] = -1;

        int sum = 0, MAX = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += (nums[i] == 1 ? 1 : -1);
            if (m.find(sum) != m.end()) MAX = max(MAX, i - m[sum]);
            if (m.find(sum) == m.end()) m[sum] = i;
        }

        return MAX;
    }
};