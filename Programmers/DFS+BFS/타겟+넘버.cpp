// 백트래킹으로 풀기
// 2^20이라 time limit X
// 한번은 더하고 다음엔 빼기

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 재귀
void find(vector<int> numbers, int target, int& ans, int index, int sum) {
    if (index >= numbers.size()) {
        if (sum == target) ans++;
        return;
    }
    // 더하기
    find(numbers, target, ans, index + 1, sum + numbers[index]);
    // 빼기
    find(numbers, target, ans, index + 1, sum - numbers[index]);
}

int solution(vector<int> numbers, int target) {
    int ans = 0; // 방법 개수
    sort(numbers.begin(), numbers.end(), greater<>());

    find(numbers, target, ans, 0, 0);

    return ans;
}