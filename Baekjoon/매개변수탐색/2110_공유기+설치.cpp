// 공유기를 집에 설치
// 가장 가까운 두 공유기의 거리를 최대로
// =============================================================================
// 파라메트릭 서치로
// 그리디하게 제일 왼쪽부터 시작해서 일정 거리 이상마다 두면서 끝까지 가능한지

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, C;          // 집, 공유기
    vector<int> house; // 집 좌표

    cin >> N >> C;
    house.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> house[i];
    }
    sort(house.begin(), house.end());

    int left = 0, right = house[N - 1] - house[0];
    int mid;

    while (left <= right) {
        mid = (left + right) / 2;
        int cnt = 1, pre = 0, next = 1;

        // 그리디하게 설치해보기
        while (next < N) {
            if (house[next] - house[pre] >= mid) {
                cnt++;
                pre = next;
            }
            next++;
        }

        if (cnt < C) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    cout << right << "\n";
}