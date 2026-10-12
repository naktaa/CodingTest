#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    queue<int> q;
    for (int i = 1; i <= N; i++)
        q.push(i);

    vector<int> ans;

    while (!q.empty()) {
        // K-1번 회전
        for (int i = 0; i < K - 1; i++) {
            q.push(q.front());
            q.pop();
        }
        // K번째 제거
        ans.push_back(q.front());
        q.pop();
    }

    // 출력 형식 맞추기
    cout << "<";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i];
        if (i != ans.size() - 1) cout << ", ";
    }
    cout << ">";

    return 0;
}
