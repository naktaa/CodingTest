#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> sizes) {
    int MAX1 = 0, MAX2 = 0; // 가로 세로 길이 최대
    int ans;
    // int MIN = 21e8;    // 넓이 최소
    for (vector<int> wallet : sizes) {
        pair<int, int> temp1 = {MAX1, MAX2}; // 가로세로 1
        pair<int, int> temp2 = {MAX1, MAX2}; // 가로세로 2
        int size1, size2;                    // 2가지 경우 크기 비교
        // cout<<len1.first<<" "<<len1.second<<"\n";
        // 가로 X 세로
        if (wallet[0] > temp1.first) temp1.first = wallet[0];
        if (wallet[1] > temp1.second) temp1.second = wallet[1];
        size1 = temp1.first * temp1.second;
        // 세로 X 가로
        if (wallet[1] > temp2.first) temp2.first = wallet[1];
        if (wallet[0] > temp2.second) temp2.second = wallet[0];
        size2 = temp2.first * temp2.second;

        // 넓이가 더 작은 경우를 갱신
        if (size1 < size2) {
            MAX1 = temp1.first;
            MAX2 = temp1.second;
        }
        else {
            MAX1 = temp2.first;
            MAX2 = temp2.second;
        }
    }

    ans = MAX1 * MAX2;
    return ans;
}