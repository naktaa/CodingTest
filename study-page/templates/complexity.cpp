#include <cstddef>
using namespace std;

int n;
long long cnt;

long long countPairs() {
    cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cnt++;
        }
    }
    return cnt;
}
