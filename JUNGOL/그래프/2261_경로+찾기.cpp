// bfs로 나오면 출력
// 거리가 1인것만 탐색
// parent 기록하면서 경로 저장
// ============================================================
// 기존 방식은 N^2*K로 최대 3천만
// 1비트씩 바꾸면서 해시맵에 있는지 확인하면 N*K로 줄어듦

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

int main() {
    int N, K; // 3 ≤ N ≤ 1,000, 2 ≤ K ≤ 30
    vector<string> code;
    vector<int> parent;
    int no1, no2;


    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        code.push_back(s);
    }
    cin >> no1 >> no2;
    parent.assign(N, -1);

    queue<int> q;
    q.push(no1 - 1);
    parent[no1 - 1] = -2;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        int flag = 0;

        for (int i = 0; i < N; i++) {
            if (now == i || parent[i] != -1) continue;
            int dist = 0;
            for (int j = 0; j < K; j++) {
                dist += abs(code[now][j] - code[i][j]);
            }

            if (dist != 1) continue;
            parent[i] = now;
            if (i == no2 - 1) {
                flag++;
                break;
            }
            q.push(i);
        }
        if (flag) break;
    }

    vector<int> path;
    if (parent[no2 - 1] == -1)
        cout << -1;
    else {
        for (int i = no2 - 1; i != -2; i = parent[i]) {
            path.push_back(i);
        }
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] + 1 << " ";
        }
    }
}

/*
5 3
000
111
010
110
001
1 2
*/