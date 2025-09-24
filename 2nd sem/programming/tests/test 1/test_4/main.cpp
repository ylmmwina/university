#include <iostream>

// завдання 4

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
public:
    SinglyLinkedList() : head(nullptr) {}

    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    bool hasPairWithSquareSum(int num) {
        int square = num * num;
        const int HASH_SIZE = 10000;
        bool hashTable[HASH_SIZE] = {false};

        Node* temp = head;
        while (temp) {
            int complement = square - temp->data;
            if (complement >= 0 && complement < HASH_SIZE && hashTable[complement]) {
                return true;
            }
            if (temp->data >= 0 && temp->data < HASH_SIZE) {
                hashTable[temp->data] = true;
            }
            temp = temp->next;
        }
        return false;
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    SinglyLinkedList list;
    list.append(3);
    list.append(1);
    list.append(7);
    list.append(5);
    list.append(9);

    int num = 4; // шукаємо пару, що дає 4^2 = 16
    if (list.hasPairWithSquareSum(num)) {
        cout << "Pair with sum " << num * num << " exists.\n";
    } else {
        cout << "No pair found with sum " << num * num << ".\n";
    }

    return 0;
}
