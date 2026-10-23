#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

        vector<int> ans;
        for (const auto& num : arr) {
            int rank = lower_bound(sorted.begin(), sorted.end(), num) - sorted.begin();
            ans.push_back(rank + 1);
        }

        return ans;
    }
};