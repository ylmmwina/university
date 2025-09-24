#include <iostream>
#include <sstream>
#include <cstring>

// завдання 2

using namespace std;

// реалізація простого стеку
class Stack {
private:
    static const int MAX_SIZE = 100;
    int data[MAX_SIZE];
    int top;
public:
    Stack() : top(-1) {}

    void push(int value) {
        if (top >= MAX_SIZE - 1) {
            cout << "Стек переповнений!" << endl;
            return;
        }
        data[++top] = value;
    }

    int pop() {
        if (top < 0) {
            cout << "Стек порожній!" << endl;
            return 0;
        }
        return data[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
};

// функція для обчислення виразу у зворотній польській нотації
int evaluateRPN(const string& expression) {
    Stack stack;
    stringstream ss(expression);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            // якщо число, додаємо його в стек
            stack.push(stoi(token));
        } else {
            // це оператор, беремо два останні значення зі стека
            int b = stack.pop();
            int a = stack.pop();
            int result = 0;

            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") result = a / b;

            stack.push(result);
        }
    }
    return stack.pop();
}

int main() {
    string expression = "3 4 + 2 * 7 /"; // (3 + 4) * 2 / 7 = 2
    cout << "Result: " << evaluateRPN(expression) << endl;
    return 0;
}
