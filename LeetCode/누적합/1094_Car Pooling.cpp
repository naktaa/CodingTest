/*
N <= 1000,
구간별로 승객 수 정해져있음
구간 진행하면서 승객의 합이 capacity 넘어가면 trip 불가
*/

#include <vector>
using namespace std;

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        int size = trips.size();
        vector<int> cntPassenger(1001, 0);
        for (const auto& trip : trips) {
            cntPassenger[trip[1]] += trip[0];
            cntPassenger[trip[2]] -= trip[0];
        }

        int sum = 0;
        for (int i = 0; i < 1001; i++) {
            sum += cntPassenger[i];
            if (sum > capacity) return false;
        }

        return true;
    }
};