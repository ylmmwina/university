#include <iostream>
#include <stack>

struct Stack {
    std::stack<int> s;
    void push(int data) {
        s.push(data);
    }
    int pop() {
        if (s.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        int top = s.top();
        s.pop();
        return top;
    }
    bool empty() const {
        return s.empty();
    }
    int top() const {
        if (s.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return s.top();
    }
};

struct Queue {
    Stack first;
    Stack second;

    void push(int data) {
        first.push(data);
    }

    int pop() {
        if (second.empty()) {
            while (!first.empty()) {
                second.push(first.pop());
            }
        }
        if (second.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return second.pop();
    }

    bool empty() const {
        return first.empty() && second.empty();
    }
};

int main() {
    Queue q;
    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << q.pop() << std::endl; // 1
    std::cout << q.pop() << std::endl; // 2

    q.push(4);
    std::cout << q.pop() << std::endl; // 3
    std::cout << q.pop() << std::endl; // 4

    return 0;
}