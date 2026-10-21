#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end());


    while (!pq.empty() && pq.top() < K) {
        int now = pq.top();
        pq.pop();
        if (pq.empty()) return -1;
        int next = pq.top();
        pq.pop();

        pq.push(now + next * 2);
        answer++;
    }

    return answer;
}