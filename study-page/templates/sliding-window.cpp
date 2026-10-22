#include <algorithm>
#include <string>
using namespace std;

string s; // ASCII 0~127
int cnt[128];
int ans;

int longestUnique() {
    int len = s.size();
    fill(cnt, cnt + 128, 0);
    int left = 0;
    ans = 0;
    for (int right = 0; right < len; right++) {
        char now = s[right];
        cnt[now]++;
        while (cnt[now] > 1) {
            char next = s[left];
            cnt[next]--;
            left++;
        }
        ans = max(ans, right - left + 1);
    }
    return ans;
}
