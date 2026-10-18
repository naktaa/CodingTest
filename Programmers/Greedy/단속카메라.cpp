// union-find?
// 개구리 문제와 비슷
// 맨 왼쪽 위치부터 오른쪽 끝 지점에 설치하면서 오기
// 시작 위치가 같으면 길이가 짧은 순대로 설치
// -------------------------------------------------------
// 나간 지점을 기준으로 잡아야함

#include <string>
#include <vector>
#include <queue>
using namespace std;

struct node {
    int start, end;
    bool operator<(node right) const {
        if (end != right.end)
            return end > right.end;
        else
            return start > right.start;
    }
};

int solution(vector<vector<int>> routes) {
    int answer = 0;
    priority_queue<node> pq;
    // pq에 모든 route 삽입해서 end 오름차순 -> start 오름차순으로 정렬
    for (vector<int> route : routes) {
        pq.push({route[0], route[1]});
    }

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();

        while (!pq.empty()) {
            node next = pq.top();
            if (next.start <= now.end) {
                pq.pop();
                continue;
            }
            break;
        }
        answer++;
    }

    return answer;
}