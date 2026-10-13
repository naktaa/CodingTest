/*
n <= 14   |   num <= 1e7
XOR 연산 값을 최소로 만드는 배열 조정
비트마스킹 dp 느낌
순차dp로 검사하면서 가보기
nums1은 순서대로 nums2만 선택하면서 가기
dp[mask] = mask 비트 고른거에서 최소값
*/

#include <vector>
using namespace std;

class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int size = nums1.size();
        const int INF = 21e8;
        vector<int> dp(1 << size, INF);
        dp[0] = 0;

        for (int visited = 0; visited < (1 << size); visited++) {
            int cnt = __builtin_popcount(visited);

            for (int i = 0; i < size; i++) {
                if (visited & (1 << i)) continue;

                int nvisited = visited | (1 << i);
                dp[nvisited] = min(dp[nvisited], dp[visited] + (nums1[cnt] ^ nums2[i]));
            }
        }

        return dp[(1 << size) - 1];
    }
};