#include <iostream>

// завдання 2

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

// додавання елемента в кінець списку
void append(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// перевірка на суму трьох елементів
bool isSumOfThree(Node* head, int n) {
    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            for (Node* k = j->next; k != nullptr; k = k->next) {
                if (i->data + j->data + k->data == n) {
                    return true;
                }
            }
        }
    }
    return false;
}

// виведення списку
void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;
    append(head, 1);
    append(head, 2);
    append(head, 3);
    append(head, 4);
    append(head, 5);
    int n;
    cout << "Enter the target sum: ";
    cin >> n;
    if (isSumOfThree(head, n)) {
        cout << "Found three elements with the sum " << n << endl;
    } else {
        cout << "No such elements found" << endl;
    }
    return 0;
}
