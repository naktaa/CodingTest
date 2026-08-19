/*
n <= 1,000,000 , -5 ≤ a ≤ -1 , |b| ≤ 10,000,000 , |c| ≤ 10,000,000 , 1 ≤ x_i ≤ 100이다.
x' = ax^2+bx+c
연속된 병사들로 특공대 구성, 특공대는 병사들의 합
최대 전투력 구하기
dp 누적합

3 2 3 2
*/

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int N, A, B, C;
    vector<ll> X;

    cin >> N >> A >> B >> C;
    X.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }

    //
}