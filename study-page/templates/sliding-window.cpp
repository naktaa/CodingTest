#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string s;
vector<int> cnt;
int ans;

int longestUnique() {
    cnt.assign(256, 0);
    int left = 0;
    ans = 0;
    for (int right = 0; right < static_cast<int>(s.size()); right++) {
        unsigned char now = s[right];
        cnt[now]++;
        while (cnt[now] > 1) {
            unsigned char next = s[left];
            cnt[next]--;
            left++;
        }
        ans = max(ans, right - left + 1);
    }
    return ans;
}
