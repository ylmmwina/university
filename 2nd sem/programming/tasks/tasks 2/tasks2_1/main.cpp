#include <iostream>
#include <stack>
#include <string>

// завдання 1

std::string decodeString(const std::string& s) {
    std::stack<int> countStack;
    std::stack<std::string> stringStack;
    std::string currentString;
    int num = 0;

    for (char ch : s) {
        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        } else if (ch == '[') {
            countStack.push(num);
            stringStack.push(currentString);
            num = 0;
            currentString.clear();
        } else if (ch == ']') {
            std::string temp = currentString;
            currentString = stringStack.top();
            stringStack.pop();
            int repeatCount = countStack.top();
            countStack.pop();
            while (repeatCount-- > 0) {
                currentString += temp;
            }
        } else {
            currentString += ch;
        }
    }

    return currentString;
}

int main() {
    std::string encodedString = "2[ab3[c]]";
    std::cout << decodeString(encodedString) << std::endl; // виведе: "abcccabccc"
    return 0;
}
