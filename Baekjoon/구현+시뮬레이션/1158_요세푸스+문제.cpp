// 링크드 리스트?
// -------------------------
// iter 생각해서 k - 1로 범위 정해줘야됨
// empty() 비어있으면 1이므로 ! 빼기
// 단순하게 arr.erase(it)가 아니라 it로 다음 위치를 다시 받아줌
// 안받아주면 쓰레기값
// 그냥 queue에 넣어서 해주는게 제일 깔끔함

#include <iostream>
#include <list>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    list<int> arr;
    for (int i = 0; i < N; i++) {
        arr.push_back(i + 1);
    }

    cout << "<";
    auto it = arr.begin();
    while (1) {
        for (int i = 0; i < K - 1; i++) {
            it++;
            if (it == arr.end()) it = arr.begin();
        }
        cout << *it;
        it = arr.erase(it);
        if (it == arr.end()) it = arr.begin();
        if (arr.empty()) break;
        cout << ", ";
    }
    cout << ">\n";
}