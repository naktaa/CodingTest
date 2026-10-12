#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int N, M;
    set<int> nums;
    vector<int> targets;

    cin >> N;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        nums.insert(num);
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        int num;
        cin >> num;
        targets.push_back(num);
    }

    for (int i = 0; i < M; i++) {
        if (nums.find(targets[i]) != nums.end())
            cout << 1 << "\n";
        else
            cout << 0 << "\n";
    }
}