#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <algorithm>
using namespace std;


/*  백트래킹으로 모든 경우 -> time limit
int n;
vector<string> nums; // 입력 받는 N개의 수
int used[16];        // 소유했는지 여부
int price[16];       // 소유할 때 가격 save
int cnt = 1;         // 백트래킹 할 때 사람 count
int ans;             // 답

//
void find(int now) {
    for (int i = 0; i < n; i++) {
        // 소유했던 사람이면 pass
        if (used[i + 1] == 1) {
            continue;
        }
        // 그림을 살 때 가격이 같거나 이상이면
        if (int(nums[now][i] - '0') >= price[now]) {
            used[i + 1] = 1;
            price[i + 1] = int(nums[now][i] - '0');
            cnt++;

            find(i + 1);

            used[i + 1] = 0;
            price[i + 1] = 0;
            cnt--;
        }
    }

    if (cnt > ans) {
        ans = cnt;
        return;
    }
}

int main() {
    cin >> n;
    nums.resize(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> nums[i + 1];
    }
    used[1] = 1;

    find(1);

    cout << ans;
}
*/


int n;                   // 예술가의 수 2 ~ 15
string price[16];        // 가격
int dp[1 << 16][16][10]; // 소유한 사람(2~15), 마지막 소유, 가격(0~9)

int bit_count(int person) {
    int cnt = 0;
    while (person > 0) {
        if ((person & 1) == 1) cnt++;
        person >>= 1;
    }
    return cnt;
}

// dfs
int find(int person, int last_person, int last_price) {
    int& cmp = dp[person][last_person][last_price]; // dp값 참조
    if (cmp != -1) return cmp;                      // 이미 계산했으면 return
    cmp = bit_count(person);

    for (int i = 0; i < n; i++) {
        // 소유한 적 있거나 가격이 더 작으면 pass
        if ((person & (1 << i)) != 0 || price[last_person][i] - '0' < last_price) continue;
        int next_person = person | (1 << i);
        cmp = max(cmp, find(next_person, i, price[last_person][i] - '0'));
    }

    return cmp;
}

// dp 풀이
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    memset(dp, -1, sizeof(dp));
    int ans = find(1, 0, 0);

    cout << ans << "\n";
}