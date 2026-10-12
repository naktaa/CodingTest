// N개의 회의에 대해 사용시간 배정
// 시작 ~ 끝
// 겹치지않게 최대한 많이
// 끝나는 시간 내림차순 + 길이 짧은거 -> 우선순위큐로 정렬
// ----------------------------------------------------------------
// 끝나는 시간 오름차순 정렬 -> 그 다음 시간 짧은 순대로

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct info {
    int start, end;
    bool operator<(info other) const {
        if (end != other.end) {
            return end > other.end;
        }
        else {
            return start > other.start; // (1,3) (3,3) 이 경우 (1,3)이 먼저 와야 만족하므로 오름차순
        }
    }
};

int main() {
    int N;
    priority_queue<info> conf;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int start, end;
        cin >> start >> end;
        conf.push({start, end});
    }

    int ans = 1;
    int last = conf.top().end;
    conf.pop();

    while (!conf.empty()) {
        info now = conf.top();
        conf.pop();

        if (now.start < last) continue; // 마지막 끝 지점보다 먼저 pass
        last = now.end;                 // 마지막 시작 지점 갱신
        ans++;
    }

    cout << ans << "\n";
}