#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct coord {
    int x, y;
};

bool cmp(coord a, coord b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<coord> point;

    cin >> N;
    while (N--) {
        int x, y;
        cin >> x >> y;
        point.push_back({x, y});
    }

    sort(point.begin(), point.end(), cmp);
    for (coord p : point) {
        cout << p.x << " " << p.y << "\n";
    }
}