#include <cstdint>
using namespace std;

unsigned long long mask;

void initMask() {
    mask = 0;
}

void addValue(int idx) { // 0 <= idx < 64
    mask |= (1ULL << idx);
}

void removeValue(int idx) {
    mask &= ~(1ULL << idx);
}

bool contains(int idx) {
    return (mask & (1ULL << idx)) != 0;
}
