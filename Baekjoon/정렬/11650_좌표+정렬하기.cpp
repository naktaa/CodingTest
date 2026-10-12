#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct coord {
    int x, y;
};

bool cmp(coord a, coord b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<coord> V;

    cin >> N;
    while (N--) {
        int x, y;
        cin >> x >> y;
        V.push_back({x, y});
    }
    sort(V.begin(), V.end(), cmp);

    for (const auto& v : V) {
        cout << v.x << " " << v.y << "\n";
    }
}