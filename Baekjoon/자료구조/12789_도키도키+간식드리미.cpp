#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    stack<int> waiting;
    int next = 1;

    for (int i = 0; i < N; ++i) {
        int student;
        cin >> student;

        while (!waiting.empty() && waiting.top() == next) {
            waiting.pop();
            ++next;
        }

        if (student == next) {
            ++next;
        }
        else {
            waiting.push(student);
        }
    }

    while (!waiting.empty() && waiting.top() == next) {
        waiting.pop();
        ++next;
    }

    if (next == N + 1 && waiting.empty()) {
        cout << "Nice";
    }
    else {
        cout << "Sad";
    }

    return 0;
}
