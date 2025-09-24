#include <iostream>

// завдання 1

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

// функція копіювання списку
Node* copyList(Node* head) {
    if (!head) return nullptr;
    Node* newHead = new Node(head->data);
    Node* current = newHead;
    head = head->next;
    while (head) {
        current->next = new Node(head->data);
        current = current->next;
        head = head->next;
    }
    return newHead;
}

// видалення елементів за індексом, кратним n
Node* removeMultiples(Node* head, int n) {
    if (n <= 0) return copyList(head);
    Node* newHead = nullptr;
    Node* current = head;
    int index = 0;
    while (current) {
        if (index % n != 0) {
            append(newHead, current->data);
        }
        current = current->next;
        index++;
    }
    return newHead;
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
    append(head, 10);
    append(head, 20);
    append(head, 30);
    append(head, 40);
    append(head, 50);
    int n;
    cout << "Enter n: ";
    cin >> n;
    Node* result = removeMultiples(head, n);
    cout << "Initial list: ";
    printList(head);
    cout << "Resulting list: ";
    printList(result);
    return 0;
}
