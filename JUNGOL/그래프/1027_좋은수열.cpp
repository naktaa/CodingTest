/*
N자리 정수 중 가장 작은 정수 찾기
반복되는 부분수열이 있으면 안됨
1 2 3 만 존재
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int N; // 1 <= N <= 80
vector<int> seq;
int found = 0;

void dfs(int idx) {
    if (idx > N) {
        for (auto num : seq) {
            cout << num;
        }
        found = 1;
        return;
    }
    else {
        for (int n = 1; n <= 3 && !found; n++) {
            if (!seq.empty() && n == seq.back()) continue;
            seq.push_back(n);
            int good = 1; // 좋은 수열 아닌지 판단

            for (int len = 1; len <= idx / 2 && good; len++) {
                good = 0;
                for (int i = 0; i < len && !good; i++) {
                    if (seq[seq.size() - 1 - i] == seq[seq.size() - 1 - len - i])
                        good = 0;
                    else {
                        good = 1;
                    }
                    // cout << "seq = ";
                    // for (auto num : seq) {
                    //     cout << num;
                    // }
                    // cout << ", [no1 no2] = " << seq[seq.size() - 1 - i] << " "
                    //      << seq[seq.size() - 1 - len - i] << ", good = " << good << "\n";
                }
            }

            if (!good) {
                seq.pop_back();
                continue;
            }

            dfs(idx + 1);
            seq.pop_back();
        }
    }
}

int main() {
    cin >> N;
    dfs(1);
}