// 1. 단순하게 100부터 + - 하기
// 2. 숫자를 눌러 가장 근접한 번호로 가서 + - 하기
// 1 <--> 2 비교해서 min값
// 100번 시작
// 각 자리와 일치하는 버튼이 존재하면 그 숫자 사용
// 재귀로 구하기 최대 10^6만큼 걸림 --> 시간 가능
// ------------------------------------------------------------
// 기존은 자릿수가 더 적은경우를 포함 안해서 오류
// 50만번이기때문에 100만까지 완탐하면 끝

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int N, M;         // 이동하려는 채널, 고장난 버튼의 개수
    set<int> buttons; // 고장난 버튼

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int button;
        cin >> button;
        buttons.insert(button);
    }

    int ans = abs(N - 100);
    string n = to_string(N);

    for (int i = 0; i < 1000000; i++) {
        string num = to_string(i);
        bool flag = true; // 버튼이 고장 안났으면 true 유지
        for (char digit : num) {
            // buttons에 있으면 고장나서 불가능이므로 false
            if (buttons.find(digit - '0') == buttons.end()) continue;
            flag = false;
            break;
        }
        if (!flag) continue;

        int cnt = abs(N - i);
        cnt += num.length();
        ans = min(ans, cnt);
    }

    cout << ans;
}