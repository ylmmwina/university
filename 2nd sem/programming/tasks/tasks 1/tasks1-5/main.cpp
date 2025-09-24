#include <iostream>

// завдання 5

using namespace std;

class MinStack {
private:
    static const int MAX_SIZE = 1000;
    int mainStack[MAX_SIZE]; // основний стек
    int minStack[MAX_SIZE];  // стек для мінімальних значень
    int topIndex;            // індекс верхнього елемента основного стеку
    int minIndex;            // індекс верхнього елемента стеку мінімумів

public:
    MinStack() : topIndex(-1), minIndex(-1) {}

    void push(int x) {
        if (topIndex >= MAX_SIZE - 1) {
            cout << "The stack is full!" << endl;
            return;
        }
        mainStack[++topIndex] = x;

        // оновлюємо minStack
        if (minIndex == -1 || x <= minStack[minIndex]) {
            minStack[++minIndex] = x;
        }
    }

    void pop() {
        if (topIndex < 0) {
            cout << "The stack is empty!" << endl;
            return;
        }
        int removed = mainStack[topIndex--];

        // якщо мінімум видаляється, видаляємо і з minStack
        if (removed == minStack[minIndex]) {
            minIndex--;
        }
    }

    int top() {
        if (topIndex < 0) {
            cout << "The stack is empty!" << endl;
            return -1;
        }
        return mainStack[topIndex];
    }

    int getMin() {
        if (minIndex < 0) {
            cout << "The stack is empty!" << endl;
            return -1;
        }
        return minStack[minIndex];
    }
};

// тестування стеку
int main() {
    MinStack s;
    s.push(5);
    s.push(3);
    s.push(7);
    s.push(2);
    cout << "Minimum element: " << s.getMin() << endl; // 2
    s.pop();
    cout << "The minimal element after pop: " << s.getMin() << endl; // 3
    s.pop();
    cout << "Top element: " << s.top() << endl; // 3
    cout << "Minimum element: " << s.getMin() << endl; // 3
    return 0;
}
