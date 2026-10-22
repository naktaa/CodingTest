#include <iostream>
using namespace std;
using ll = long long;

int N;
ll cnt;

ll countPairs() {
    cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cnt++;
        }
    }
    return cnt;
}
