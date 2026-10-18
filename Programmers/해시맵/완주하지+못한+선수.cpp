// 해쉬맵 사용해서 참가자수 먼저 세기 --> 완주한 사람들 수 -1

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map<string, int> map;
    for (string player : participant) {
        if (map.find(player) == map.end())
            map[player] = 1;
        else {
            int num = map[player];
            map[player] = num + 1;
        }
    }
    // for (auto m : map) {
    //     cout<<m.first<<" "<<m.second<<"\n";
    // }

    for (string c : completion) {
        int num = map[c];
        map[c] = num - 1;
    }
    for (auto m : map) {
        if (m.second == 0) continue;
        answer += m.first;
        break;
    }

    return answer;
}