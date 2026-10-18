// 최대 2명
// 무거운 순서대로 선택하면서 가장 낮은 몸무게와 조합했을 때 가능하면 -2 안되면 -1
// 정렬하고 앞 뒤 삭제 가능한 deque 사용

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    deque<int> people_new;

    for (int person : people) {
        people_new.push_back(person);
    }
    sort(people_new.begin(), people_new.end(), greater<int>());

    while (!people_new.empty()) {
        int sum = people_new[0] + people_new[people_new.size() - 1]; // 가장 무거운 + 가장 가벼운
        if (sum <= limit) {
            people_new.pop_front();
            if (!people_new.empty()) people_new.pop_back(); // 마지막에 1개 남았을 때 처리
        }
        else
            people_new.pop_front();
        answer++;
    }


    return answer;
}