// xy+z     --> xyz, xyyz, xyyyz
// (xyz)    --> xyz, xyzxyz, xyzxyzxyz
// x+ | y+  --> x, y, xx, yyy
// (100+1+ | 01)+ 를 만족하는 패턴인지 확인
// ------------------------------------------------------
// 상태 머신 (state machine) 활용

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> wave;

int main() {
    int T;
    cin >> T;
    wave.resize(T);
    for (int i = 0; i < T; i++) {
        cin >> wave[i];
    }

    for (string target : wave) {
        int index = 0; // 인덱스 체크용
        int flag = 0;  // 0 --> 패턴 전, 1 --> 01 패턴 시작, 2 --> 100+1+ 패턴 시작
                       // 3 --> 100+1+ 에서 10까지 확인, 4 --> 100+1+ 에서 0+ 확인
                       // 5 --> 100+1+ 에서 1+ 한번 확인, 6 --> 100+1+ 에서 1+ 유지중
                       // 7 --> 100+1+~ 에서 0 나온 상황, -1 --> NO 출력

        // 패턴 길이만큼 파싱 시작
        while (index < target.size()) {
            int num = target[index++] - '0';
            // cout << "flag: " << flag << ", num: " << num << " | ";

            // 패턴 시작 전
            if (flag == 0) {
                if (num == 0) {
                    flag = 1;
                }
                else {
                    flag = 2;
                }
            }
            // 01 확인중
            else if (flag == 1) {
                if (num == 1) {
                    flag = 0; // 01 확인했으면 초기 상태로 돌아감
                }
                else {
                    flag = -1; // 00 인 경우 NO 출력
                    break;
                }
            }
            // 10 확인중
            else if (flag == 2) {
                if (num == 0) {
                    flag = 3;
                }
                else {
                    flag = -1; // 11 인 경우 NO 출력
                    break;
                }
            }
            // 100+ 확인중
            else if (flag == 3) {
                if (num == 0) {
                    flag = 4; // 0+ 확인했으면 1+로 넘어감
                }
                else {
                    flag = -1;
                    break;
                }
            }
            // 1+ 확인중에 0 계속 나오면 flag 4 유지, 1 나오면 flag 5
            else if (flag == 4) {
                if (num == 1) {
                    flag = 5;
                }
            }
            // 100+1+ 까지 확인 0 나오면 01로, 1 나오면 flag 6
            else if (flag == 5) {
                if (num == 0) {
                    flag = 1;
                }
                else {
                    flag = 6;
                }
            }
            // 100+1+ 에서 1+ 유지중
            else if (flag == 6) {
                if (num == 0) {
                    flag = 7;
                }
            }
            // 1+ 유지하다 0 나온 상태
            else if (flag == 7) {
                if (num == 1) {
                    flag = 0; // 01 확인했으니 초기상태 flag 0 으로
                }
                else {
                    flag = 4; // 100+ 까지 확인
                }
            }
        }

        // 파싱 종료 후 YES OR NO 출력
        if (flag == 0 || flag == 5 || flag == 6) {
            cout << "YES" << "\n";
        }
        else {
            cout << "NO" << "\n";
        }
    }
}
/*
int main() {
    int T;
    cin >> T;
    wave.resize(T);
    for (int i = 0; i < T; i++) {
        cin >> wave[i];
    }

    // cout << "\n";

    for (string num : wave) {
        int index = 0; // 인덱스 체크용
        int flag = 0;  // 0이면 YES, 1이면 NO

        while (1) {
            // 끝까지 다 파싱하면 종료
            if (index >= num.size()) {
                break;
            }
            else {
                // 100+1+ 패턴
                if (num[index] == '1') {
                    // cout << index << ": " << num[index] << " | ";
                    index++;
                    if (index >= num.size()) {
                        flag = 1;
                        break;
                    }
                    // 11로 시작하면 NO 출력
                    if (num[index] == '1') {
                        // cout << index << ": " << num[index] << " | ";
                        flag = 1;
                        break;
                    }
                    // 10 시작
                    else {
                        // cout << index << ": " << num[index] << " | ";
                        int next0 = 0; // 0+ 시작했는지 확인
                        int next1 = 0; // 1+ 시작했는지 확인
                        index++;
                        if (index >= num.size()) {
                            flag = 1;
                            break;
                        }

                        while (1) {
                            if (index >= num.size()) {
                                flag = 1;
                                break;
                            }
                            // 1
                            if (num[index] == '1') {
                                // 0+ 안했는데 1 나오면 NO
                                if (next0 == 0) {
                                    flag = 1;
                                    break;
                                }
                                else {
                                    index++;
                                    next1++;
                                }
                            }
                            // 0
                            else {
                                // 1+ 시작하지 않았으면 진행
                                if (next1 == 0) {
                                    index++;
                                    next0++;
                                }
                                // 1+ 시작했으면 종료
                                else {
                                    break;
                                }
                            }
                            // cout << index << ": " << num[index] << " | ";
                        }
                        if (next0 == 0 || next1 == 0) {
                            flag = 1;
                            break;
                        }
                    }
                }
                // 01 패턴
                else {
                    // cout << index << ": " << num[index] << " | ";
                    index++;
                    // 00 이므로 NO 출력
                    if (num[index] == '0') {
                        // cout << index << ": " << num[index] << " | ";
                        flag = 1;
                        break;
                    }
                    // 01
                    else {
                        // cout << index << ": " << num[index] << " | ";
                        index++;
                    }
                }
            }
        }
        if (flag == 1) {
            cout << "NO" << "\n";
        }
        else {
            cout << "YES" << "\n";
        }
    }
}
*/

/*
3
10010111
011000100110001
0110001011001
*/