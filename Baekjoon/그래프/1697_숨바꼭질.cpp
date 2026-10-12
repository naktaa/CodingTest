#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    int visited[210000] = {0};
    cin >> N >> K;


    queue<int> q;
    q.push(N);
    visited[N] = 1;

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (now == K) break;

        for (int i = 0; i < 3; i++) {
            int next = 1;
            switch (i) {
            case 0:
                next = now * 2;
                break;
            case 1:
                next = now + 1;
                break;
            case 2:
                next = now - 1;
                break;
            }

            if (next < 0 || next >= 210000) continue;
            if (visited[next] > 0) continue;
            visited[next] = visited[now] + 1;
            q.push(next);
        }
    }

    cout << visited[K] - 1;
}