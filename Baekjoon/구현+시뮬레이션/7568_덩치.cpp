#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<pair<int, int>> people;
    while (N--) {
        int w, h;
        cin >> w >> h;
        people.push_back({w, h});
    }

    for (const auto& a : people) {
        int rank = 1;
        for (const auto& b : people) {
            if (a.first < b.first && a.second < b.second) rank++;
        }
        cout << rank << " ";
    }
}