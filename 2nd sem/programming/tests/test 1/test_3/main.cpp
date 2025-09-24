#include <iostream>
#include <algorithm>

// завдання 3

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// додавання елемента в кінець циклічного списку
void append(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
        return;
    }
    Node* tail = head->prev;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = head;
    head->prev = newNode;
}

// перетворення списку в масив і сортування
int* listToArray(Node* head, int& size) {
    if (!head) {
        size = 0;
        return nullptr;
    }
    size = 0;
    Node* current = head;
    do {
        size++;
        current = current->next;
    } while (current != head);

    int* arr = new int[size];
    current = head;
    for (int i = 0; i < size; ++i) {
        arr[i] = current->data;
        current = current->next;
    }
    sort(arr, arr + size);
    return arr;
}

// перевірка можливості формування першого списку з другого
bool canFormFirstList(Node* first, Node* second) {
    int size1, size2;
    int* arr1 = listToArray(first, size1);
    int* arr2 = listToArray(second, size2);

    if (size1 > size2) return false;

    for (int i = 0; i < size1; ++i) {
        bool found = false;
        for (int j = 0; j < size2; ++j) {
            if (arr1[i] == arr2[j]) {
                arr2[j] = -1; // Позначаємо елемент як використаний
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

// виведення циклічного списку
void printList(Node* head) {
    if (!head) return;
    Node* current = head;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}

int main() {
    Node* list1 = nullptr;
    Node* list2 = nullptr;
    append(list1, 6);
    append(list1, 8);
    append(list1, 12);
    append(list2, 2);
    append(list2, 4);
    append(list2, 3);
    cout << "List 1: ";
    printList(list1);
    cout << "List 2: ";
    printList(list2);
    if (canFormFirstList(list1, list2)) {
        cout << "List 1 can be formed from List 2" << endl;
    } else {
        cout << "List 1 cannot be formed from List 2" << endl;
    }
    return 0;
}
