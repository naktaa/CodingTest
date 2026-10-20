/*
N <= 1e5, -1e4 <= num <= 1e4
nums에서 k번째까지 많이 나오는 숫자 출력
sort
음수가 있어서 그냥 배열 말고 해시맵으로
map value 기준으로 정렬하려면 pair 벡터로 변환해서 cmp 만들어주기
================================================
버킷 정렬 활용하기
버킷 정렬: 빈도수를 기준으로 해서 vector에 채워주기
*/
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
    static bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }

public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int len = nums.size();

        unordered_map<int, int> m;
        for (int i = 0; i < len; i++) {
            m[nums[i]]++;
        }

        vector<pair<int, int>> v(m.begin(), m.end());
        sort(v.begin(), v.end(), cmp);

        vector<int> ans;
        for (int i = 0; i < k; i++) {
            ans.push_back(v[i].first);
        }

        return ans;
    }
};

/* 버킷 정렬
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int len = nums.size();

        unordered_map<int, int> m;
        for (int num : nums) {
            m[num]++;
        }

        vector<vector<int>> bucket(len + 1);
        for (const auto& p : m) {
            bucket[p.second].push_back(p.first);
        }

        vector<int> ans;
        for (int i = len; i >= 1; i--) {
            for (int num : bucket[i]) {
                ans.push_back(num);

                if (static_cast<int>(ans.size()) == k) {
                    return ans;
                }
            }
        }

        return ans;
    }
};
*/