#include <iostream>

// завдання 3

using namespace std;

// оголошення структури вузла однозв’язного списку
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// функція для перевірки, чи є список паліндромом
bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;

    // 1) знайти середину списку(коли fast дійде до кінця, slow дійде до середини)
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 2) розвернути другу половину списку
    ListNode* prev = nullptr, *curr = slow;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // 3) порівняти обидві половини
    ListNode* left = head, *right = prev;
    while (right) {
        if (left->val != right->val) return false;
        left = left->next;
        right = right->next;
    }

    return true;
}

// допоміжна функція для створення списку
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

// головна функція для перевірки
int main() {
    ListNode* head = createList({1, 2, 3, 2, 1});
    cout << (isPalindrome(head) ? "The list is a palindrome" : "The list is not a palindrome") << endl;

    return 0;
}
