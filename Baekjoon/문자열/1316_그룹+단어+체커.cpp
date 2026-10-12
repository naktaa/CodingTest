#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    int alpha[26];
    int cnt = 0;

    while (N--) {
        memset(alpha, 0, sizeof(alpha));
        int flag = 1;
        string word;
        cin >> word;


        for (int i = 0; i < word.length(); i++) {
            if (alpha[word[i] - 'a']) {
                flag = 0;
                break;
            }
            if (i < word.length() - 1 && word[i + 1] == word[i]) continue;
            alpha[word[i] - 'a'] = 1;
        }

        if (flag) cnt++;
    }

    cout << cnt << "\n";
}