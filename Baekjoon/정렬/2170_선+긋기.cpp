#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct line {
    int x, y;
};

bool cmp(line a, line b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<line> lines;
    int start = -1e9, end = -1e9;
    int ans = 0;

    cin >> N;
    lines.resize(N);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        lines[i] = {x, y};
    }
    sort(lines.begin(), lines.end(), cmp);

    for (int i = 0; i < N; i++) {
        if (lines[i].x <= end) {
            if (lines[i].y > end) {
                end = lines[i].y;
            }
        }
        else {
            ans += (end - start);
            start = lines[i].x;
            end = lines[i].y;
        }
    }
    ans += (end - start);

    cout << ans << "\n";
}