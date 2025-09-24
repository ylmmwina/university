#include <iostream>

// завдання 4

using namespace std;

// визначення структури вузла списку
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// функція для перестановки вузлів
ListNode* oddEvenList(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* odd = head;        // початок списку непарних
    ListNode* even = head->next; // початок списку парних
    ListNode* evenHead = even;   // зберігаємо початок парного списку

    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;

        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead; // з’єднуємо непарний і парний списки
    return head;
}

// функція для створення списку
ListNode* createList(initializer_list<int> vals) {
    ListNode* head = nullptr, *tail = nullptr;
    for (int val : vals) {
        if (!head) {
            head = tail = new ListNode(val);
        } else {
            tail->next = new ListNode(val);
            tail = tail->next;
        }
    }
    return head;
}

// функція для виводу списку
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    ListNode* head = createList({1, 2, 3, 4, 5});
    cout << "Incoming list: ";
    printList(head);

    head = oddEvenList(head);
    cout << "Result: ";
    printList(head);

    return 0;
}
