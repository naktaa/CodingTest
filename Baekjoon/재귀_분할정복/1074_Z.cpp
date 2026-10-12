#include <iostream>
#include <vector>
#include <cstring>
#include <string.h>
#include <cmath>
using namespace std;


int main() {
    int n;
    int r, c;
    vector<int> position;
    int length = 1;
    int result = 0;

    cin >> n >> r >> c;
    for (int i = 0; i < n; i++) {
        length *= 2;
    }

    for (int i = 0; i < n; i++) {
        length /= 2;
        if (r < length && c >= length) {
            c -= length;
            result += 1 * pow(length, 2);
        }
        else if (r >= length && c < length) {
            r -= length;
            result += 2 * pow(length, 2);
        }
        else if (r >= length && c >= length) {
            c -= length;
            r -= length;
            result += 3 * pow(length, 2);
        }
    }

    cout << result;
}