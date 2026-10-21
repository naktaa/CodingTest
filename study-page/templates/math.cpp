#include <cstdint>
using namespace std;

long long gcdValue(long long a, long long b) { // a, b >= 0
    while (b != 0) {
        long long next = a % b;
        a = b;
        b = next;
    }
    return a;
}
