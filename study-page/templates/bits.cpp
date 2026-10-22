#include <iostream>
using namespace std;

int mask; // 원소 번호 0~19, N <= 20

void initMask() {
    mask = 0;
}

void addValue(int idx) { // 0 <= idx < 20
    mask |= (1 << idx);
}

void removeValue(int idx) {
    mask &= ~(1 << idx);
}

bool contains(int idx) {
    return (mask & (1 << idx)) != 0;
}
