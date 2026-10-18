// 각 전화번호부를 해시맵에 넣고
// 모든 접두어를 하나씩 해시맵에 있는지 확인
// test

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    unordered_map<string, int> nums;
    for (string num : phone_book) {
        string save = "";
        for (char c : num) {
            save += c;
            if (nums.find(save) == nums.end())
                nums[save] = 1;
            else
                nums[save]++;
        }
    }

    for (const auto& num : phone_book) {
        if (nums[num] == 1) continue;
        answer = false;
        break;
    }
    return answer;
}