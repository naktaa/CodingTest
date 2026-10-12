// 수열의 원소를 바꿔서 오름차순으로 만들기
// 3번 안에 성공
// ----------------------------------------------
// 단순하게 i, i+1 비교하면 틀림
// 최장 증가 부분수열 LIS 관련 문제
// algorithm 이진탐색 upper_bound 쓰기

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;              // 수열의 길이
int A[200001];      // 수열
int dp[200001];     // LIS 최소값 저장
int cnt;            // 연산 횟수
int index[200001];  // LIS마다 마지막 수의 index를 저장
int parent[200001]; // LIS 갱신마다 앞 원소의 index를 부모 index로 저장
int check[200001];
vector<int> ans_index;
vector<int> ans_num;

int main() {
    cin >> N;
    for (int i = 1; i < N + 1; i++) {
        cin >> A[i];
    }

    index[0] = -1;
    parent[0] = -1;

    for (int i = 1; i <= N; i++) {
        int lis = upper_bound(dp, dp + cnt + 1, A[i]) - dp;
        if (i == 1) lis = 1;
        dp[lis] = A[i];
        index[lis] = i;
        parent[i] = index[lis - 1];
        // 최장길이 갱신
        if (lis > cnt) cnt++;
    }

    if (N - cnt > 3) {
        cout << "NO" << "\n";
    }
    else {
        int track = index[cnt];
        int last = 1;
        while (track != -1) {
            check[track] = 1;
            track = parent[track];
        }
        for (int i = 1; i <= N; i++) {
            if (check[i] == 1) {
                last = A[i];
                continue;
            }
            ans_index.push_back(i);
            ans_num.push_back(last);
        }
        cout << "YES" << "\n";
        cout << N - cnt << "\n";
        for (int i = 0; i < N - cnt; i++) {
            cout << ans_index[i] << " " << ans_num[i] << "\n";
        }
    }
}