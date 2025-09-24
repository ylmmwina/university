#include <iostream>
#include <stack>
#include <string>

// завдання 2

bool isBalanced(const std::string& s) {
    std::stack<char> bracketStack;

    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            bracketStack.push(ch);
        } else {
            if (bracketStack.empty()) return false;
            char top = bracketStack.top();
            if ((ch == ')' && top == '(') ||
                (ch == ']' && top == '[') ||
                (ch == '}' && top == '{')) {
                bracketStack.pop();
                } else {
                    return false;
                }
        }
    }
    return bracketStack.empty();
}

int main() {
    std::string input;
    std::cout << "Enter the line with brackets: ";
    std::cin >> input;

    if (isBalanced(input)) {
        std::cout << "The line is balanced." << std::endl;
    } else {
        std::cout << "The line is unbalanced. " << std::endl;
    }

    return 0;
}