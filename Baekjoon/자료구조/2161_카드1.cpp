#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    queue<int> q;

    cin >> N;
    for (int i = 1; i <= N; i++) {
        q.push(i);
    }

    while (q.size() != 1) {
        cout << q.front() << " ";
        q.pop();

        int next = q.front();
        q.pop();
        q.push(next);
    }
    cout << q.front();
}