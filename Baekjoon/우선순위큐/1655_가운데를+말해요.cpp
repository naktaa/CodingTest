// ------------------------------------------------------------------------------------------
// 단순하게 pq 하나로 중간값 못찾음
// 내부는 정렬되어있지 않고 계속 복사해서 찾으면 time limit
// 최대힙 최소힙으로 2개 만들어서 관리

#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    priority_queue<int> prior;                           // 중간값보다 작은 값들 저장 내림차순
    priority_queue<int, vector<int>, greater<int>> back; // 중간값보다 큰 값들 저장 오름차순

    while (N--) {
        int n;
        cin >> n;

        // 앞에거 비었거나  push
        if (prior.empty() || n < prior.top())
            prior.push(n);
        else
            back.push(n);

        // 앞에가 개수가 더 많으면 뒤로 보내서 조정
        if (prior.size() > back.size() + 1) {
            back.push(prior.top());
            prior.pop();
        }
        else if (prior.size() < back.size()) {
            prior.push(back.top());
            back.pop();
        }

        cout << prior.top() << "\n";
    }
}