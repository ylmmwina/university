#include <iostream>

// завдання 5

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

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

    void createCycle(int pos) {
        if (!head) return;
        Node* temp = head;
        Node* cycleNode = nullptr;
        int count = 1;
        while (temp->next) {
            if (count == pos) cycleNode = temp;
            temp = temp->next;
            count++;
        }
        if (cycleNode) temp->next = cycleNode;
    }

    int findCycleStart() {
        const int HASH_SIZE = 10000;
        Node* hashTable[HASH_SIZE] = {nullptr};

        Node* temp = head;
        int index = 1;
        while (temp) {
            int hashIndex = ((uintptr_t)temp) % HASH_SIZE;
            if (hashTable[hashIndex] == temp) {
                return index;
            }
            hashTable[hashIndex] = temp;
            temp = temp->next;
            index++;
        }
        return -1;
    }

    ~LinkedList() {
        Node* slow = head;
        Node* fast = head;
        bool cycle = false;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                cycle = true;
                break;
            }
        }
        if (cycle) {
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            fast->next = nullptr;
        }

        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);
    list.append(6);

    list.createCycle(3);

    int cycleStart = list.findCycleStart();
    if (cycleStart != -1) {
        cout << "Cycle starts at node index: " << cycleStart << endl;
    } else {
        cout << "No cycle detected." << endl;
    }

    return 0;
}
