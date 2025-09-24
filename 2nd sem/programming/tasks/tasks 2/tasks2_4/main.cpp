#include <iostream>
#include <stack>
#include <vector>

// завдання 4

bool validateStackSequences(const std::vector<int>& pushOrder, const std::vector<int>& popOrder) {
    std::stack<int> st;
    int j = 0;

    for (int num : pushOrder) {
        st.push(num);
        while (!st.empty() && st.top() == popOrder[j]) {
            st.pop();
            j++;
        }
    }

    return st.empty();
}

int main() {
    std::vector<int> pushOrder = {1, 2, 3, 4, 5};
    std::vector<int> popOrder = {4, 5, 3, 2, 1};

    if (validateStackSequences(pushOrder, popOrder)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }

    return 0;
}
