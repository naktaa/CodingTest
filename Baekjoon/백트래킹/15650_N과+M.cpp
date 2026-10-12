// N개 중에 중복 없이 M개 수열 - 오름차순
// 2 1 3 X

#include <iostream>
#include <vector>
using namespace std;

int N, M;
int visited[8]; // 방문 여부
int path[8];    // path

void func(int level) {
    // M개 고르면 출력하고 return
    if (level == M) {
        for (int i = 0; i < M; i++) {
            cout << path[i] << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;                            // 중복 pass
        if (level >= 1 && i + 1 < path[level - 1]) continue; // 오름차순 아닌 경우 pass

        visited[i] = 1;
        path[level] = i + 1;
        func(level + 1);
        visited[i] = 0;
        path[level] = 0;
    }
}

int main() {
    cin >> N >> M;

    func(0);
}