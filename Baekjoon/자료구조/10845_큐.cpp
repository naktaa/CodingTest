#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    Node q;
    Node *Head = nullptr, *Tail = nullptr;
    cin >> N;

    while (N--) {
        string com; // 명령
        cin >> com;

        if (com == "push") {
            int num;
            cin >> num;
            Node* temp = new Node;
            temp->data = num;
            temp->next = nullptr;

            if (Head == nullptr) {
                Head = Tail = temp;
            }
            else {
                Tail->next = temp;
                Tail = temp;
            }
        }
        else if (com == "pop") {
            if (Head == nullptr) {
                cout << -1 << "\n";
            }
            else {
                int temp = Head->data;
                cout << temp << "\n";
                Head = Head->next;
            }
        }
        else if (com == "size") {
            int size = 0;
            Node* now = Head;
            while (now) {
                size++;
                now = now->next;
            }
            cout << size << "\n";
        }
        else if (com == "empty") {
            if (Head == nullptr) {
                cout << 1 << "\n";
            }
            else {
                cout << 0 << "\n";
            }
        }
        else if (com == "front") {
            if (Head == nullptr) {
                cout << -1 << "\n";
            }
            else {
                cout << Head->data << "\n";
            }
        }
        else if (com == "back") {
            if (Head == nullptr) {
                cout << -1 << "\n";
            }
            else {
                cout << Tail->data << "\n";
            }
        }
    }
}