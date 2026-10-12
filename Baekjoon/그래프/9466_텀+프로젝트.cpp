/*
자기 자신을 선택하는 경우 --> 혼자 한 팀
다른 사람을 선택하는 경우 --> 싸이클을 이루면 한 팀
싸이클 검사
1
7
3 1 3 7 3 4 6
1
8
1 2 3 4 5 6 7 8
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int N, team = 0; // 학생 수, 팀 이룬 수
        vector<int> no;
        vector<int> visited;

        cin >> N;
        no.resize(N + 1, 0);
        visited.resize(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            cin >> no[i];
        }

        for (int i = 1; i <= N; i++) {
            if (visited[i])
                continue;
            else {
                vector<int> cycle;
                int next;

                for (next = i; !visited[next]; next = no[next]) {
                    cycle.push_back(next);
                    visited[next] = 1;
                }

                for (int idx = cycle.size() - 1; idx >= 0; idx--) {
                    if (cycle[idx] != next) continue;
                    team += (cycle.size() - idx);
                    break;
                }
            }
        }

        cout << N - team << "\n";
    }
}