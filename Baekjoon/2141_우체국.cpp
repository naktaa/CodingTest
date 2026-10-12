/*
최대 10만 다 탐색하면 시간 초과 가능성 - O(N^2)
========================================================================================
좌표 오름차순 정렬 --> 인구의 절반인 지점

3
1 3
2 5
3 3
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    int N;
    vector<ll> X; // 마을의 위치
    vector<ll> A; // 사람 수
    ll cntA = 0;

    cin >> N;
    X.resize(N);
    A.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
        cin >> A[i];
        cntA += A[i];
    }
}