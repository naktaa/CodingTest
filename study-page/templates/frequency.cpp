#include <map>
#include <vector>
using namespace std;

vector<int> nums;
map<int, int> cnt;

void countValues() {
    cnt.clear();
    for (int now : nums) {
        cnt[now]++;
    }
}

void removeValue(int now) {
    auto it = cnt.find(now);
    if (it == cnt.end()) return;
    it->second--;
    if (it->second == 0) {
        cnt.erase(it);
    }
}
