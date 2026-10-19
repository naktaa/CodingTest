/*
N <= 1e5
알파벳을 하나만 사용하는 가장 긴 부분문자열
right 늘려가면서 중복 확인
중복되면 left 땡기기
*/
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        unordered_set<char> visited;

        int left = 0, right = 0;
        int MAX = 0;

        while (left < len && right < len) {
            if (visited.find(s[right]) != visited.end()) {
                MAX = max(MAX, right - left);

                while (visited.find(s[right]) != visited.end()) {
                    visited.erase(s[left]);
                    left++;
                }
            }
            else {
                visited.insert(s[right]);
                right++;
            }
            /* 개선
            while (visited.find(s[right]) != visited.end()) {
                visited.erase(s[left]);
                left++;
            }

            visited.insert(s[right]);
            MAX = max(MAX, right - left + 1);
            */
        }
        MAX = max(MAX, right - left);

        return MAX;
    }
};