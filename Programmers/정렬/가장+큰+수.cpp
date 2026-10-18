// 조합 자릿수는 동일
// 앞에서부터 숫자가 클수록 가장 큰 수
// 모든 조합 따지기엔 너무 많음 0~1000 -> 최대 10만개
// 978 9 8 8 어떻게 판별할지
// 최대 4자리니 struct 를 4자리 string으로 만들어서 판별
// 953 판단하려면 9 가능한지 9 시작이 없으면 무조건 가능 있으면 그 다음 숫자들 판단 해야됨
// 34 같이 n[1]이 n[0]보다 큰 경우 예외처리
// ------------------------------------------------------------------------------------------
// 기존 로직은 40, 403 반례에 걸림
// a 3 비교할 때 3+a가 되어 40340 순서가 되버림
// 단순하게 a + b / b + a 비교하면 끝

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct numtoString {
    char n[4];
    string number;
};

// bool compare (numtoString s1, numtoString s2) {
//     // n[0] 판별
//     if (s1.n[0] != s2.n[0]) return s1.n[0] > s2.n[0];
//     else {
//         // n[1] 판별
//         if (s1.n[1] != s2.n[1]) {
//             char temp11 = s1.n[1];    // 임시 비교값
//             char temp12 = s2.n[1];    // 임시 비교값
//             if (s1.n[1] > s1.n[0] && s1.n[1] <= '9') temp11 = s1.n[1] + 'a' - '0';
//             if (s2.n[1] > s2.n[0] && s2.n[1] <= '9') temp12 = s2.n[1] + 'a' - '0';
//             return temp11 > temp12;
//         }
//         else {
//             // n[2] 판별
//             if (s1.n[2] != s2.n[2]) {
//                 char temp21 = s1.n[2];    // 임시 비교값
//                 char temp22 = s2.n[2];    // 임시 비교값
//                 if (s1.n[2] > s1.n[1] && s1.n[2] <= '9') temp21 = s1.n[2] + 'a' - '0';
//                 if (s2.n[2] > s2.n[1] && s2.n[2] <= '9') temp22 = s2.n[2] + 'a' - '0';
//                 return temp21 > temp22;
//             }
//             else {
//                 // n[3] 판별
//                 if (s1.n[3] != s2.n[3]) {
//                     char temp31 = s1.n[3];    // 임시 비교값
//                     char temp32 = s2.n[3];    // 임시 비교값
//                     if (s1.n[3] > s1.n[2] && s1.n[3] <= '9') temp31 = s1.n[3] + 'a' - '0';
//                     if (s2.n[3] > s2.n[2] && s2.n[3] <= '9') temp32 = s2.n[3] + 'a' - '0';
//                     return temp31 > temp32;
//                 }
//             }
//         }
//     }
// }

bool compare(string a, string b) {
    return a + b > b + a;
}

string solution(vector<int> numbers) {
    string answer = "";
    numtoString nums[numbers.size()];
    vector<string> numbers_new;
    // for (int i = 0; i < numbers.size(); i++) {
    //     nums[i].number = to_string(numbers[i]);
    //     string temp = to_string(numbers[i]);
    //     for (int index = 0; index < temp.length(); index++) {
    //         nums[i].n[index] = temp[index];
    //     }
    //     for (int j = 0; j < 4; j++) {
    //         if (nums[i].n[j] >= '0' && nums[i].n[j] <= '9') continue;
    //         nums[i].n[j] = 'a';   // 0~9보다 큰 값
    //     }
    // }
    for (int number : numbers) {
        string num = to_string(number);
        numbers_new.push_back(num);
    }

    // sort(nums, nums + numbers.size(), compare);
    sort(numbers_new.begin(), numbers_new.end(), compare);

    for (string num : numbers_new) {
        answer += num;
    }
    if (answer[0] == '0') answer = '0';
    return answer;
}