#include <iostream>
#include <vector>
using namespace std;

int main() {
    int h, w;
    vector<vector<int>> grid;

    cin >> h >> w;
    grid.assign(h, vector<int>(w, 0));
    for (int y = 0; y < w; y++) {
        for (int x = 0; x < h; x++) {
            cin >> grid[y][x];
        }
    }
}