#include <iostream>
#include <queue>
using namespace std;

// 1초 후에 -1 or +1
// 0초 후에 *2
// N --> K 가장 빠른 시간

struct node {
    int pos, time; // 위치, 시간
    bool operator<(node right) const {
        return time > right.time;
    }
};
int N, K;      // 수빈, 동생
int T[100001]; // 시간

void dijkstra(int start) {
    for (int i = 0; i <= 100000; i++) {
        T[i] = 21e8;
    }
    T[start] = 0;
    priority_queue<node> pq;
    pq.push({start, 0});

    while (!pq.empty()) {
        node now = pq.top();
        pq.pop();
        if (now.time > T[now.pos]) continue; // T 값보다 크면 pass

        // 순간이동
        int npos = now.pos * 2;
        if (npos >= 0 && npos <= 100000 && now.time < T[npos]) {
            T[npos] = now.time;
            pq.push({npos, now.time});
        }
        // X-1 이동
        npos = now.pos - 1;
        if (npos >= 0 && npos <= 100000 && now.time + 1 < T[npos]) {
            T[npos] = now.time + 1;
            pq.push({npos, now.time + 1});
        }
        // X+1 이동
        npos = now.pos + 1;
        if (npos >= 0 && npos <= 100000 && now.time + 1 < T[npos]) {
            T[npos] = now.time + 1;
            pq.push({npos, now.time + 1});
        }
    }
}

int main() {
    cin >> N >> K;

    dijkstra(N);

    cout << T[K];
}