/*
겹치는 구간이 있으면 합치기
union find?
아니면 idx 별로 flag 남겨놓고 순회하면서 배열 만들기
구간 시작이면 +1, 끝이면 -1
0부터 진행하면서 flag 합이 0이 되면 구간 만들어짐 +1 +1 -1 -1
===============================================================
그리디하게 정렬
순회하면서 right 부분 비교해서 갱신
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> ans;
        for (const auto& interval : intervals) {
            if (ans.empty() || ans.back()[1] < interval[0]) {
                ans.push_back(interval);
            }
            else {
                ans.back()[1] = max(ans.back()[1], interval[1]);
            }
        }

        return ans;
    }
};