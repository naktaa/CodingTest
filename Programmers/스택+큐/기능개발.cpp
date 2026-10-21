/*
7 4 9 6
*/

#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int size = speeds.size();
    int cnt = 0, last = 0;

    for (int i = 0; i < size; i++) {
        int rest = 100 - progresses[i];
        int period = rest / speeds[i] + ((rest % speeds[i] == 0) ? 0 : 1);

        if (answer.empty() || period > last) {
            answer.push_back(1);
            last = period;
        }
        else
            answer.back()++;
    }

    return answer;
}