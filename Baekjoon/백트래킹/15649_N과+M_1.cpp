// 1~N 중 중복 X M개 고르기

#include <iostream>
#include <vector>
using namespace std;

void func(int depth, int N, int M, vector<int>& visited, vector<int>& path) {
    // M개 고르면 cnt 증가시키고 return
    if (depth == M) {
        for (int i = 0; i < depth; i++) {
            cout << path[i] + 1 << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = 0; i < N; i++) {
        if (visited[i]) continue; // 중복 제거
        visited[i] = 1;
        path[depth] = i;
        func(depth + 1, N, M, visited, path);
        visited[i] = 0;
    }
}

int main() {
    int N, M;
    vector<int> visited; // 백트래킹 방문 여부
    vector<int> path;
    cin >> N >> M;
    visited.resize(N);
    path.resize(M);

    func(0, N, M, visited, path);
}