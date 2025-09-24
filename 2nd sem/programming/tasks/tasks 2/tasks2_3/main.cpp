#include <iostream>
#include <stack>
#include <queue>

// завдання 3

class Queue {
private:
    std::queue<int> q;
public:
    void enqueue(int value) {
        q.push(value);
    }
    void dequeue() {
        if (!q.empty()) q.pop();
    }
    bool isEmpty() {
        return q.empty();
    }
    int front() {
        return q.front();
    }
    int size() {
        return q.size();
    }
    void reverseFirstK(int k) {
        if (q.empty() || k <= 0 || k > q.size()) return;
        std::stack<int> s;

        for (int i = 0; i < k; ++i) {
            s.push(q.front());
            q.pop();
        }

        while (!s.empty()) {
            q.push(s.top());
            s.pop();
        }

        int remaining = q.size() - k;
        while (remaining-- > 0) {
            q.push(q.front());
            q.pop();
        }
    }
    void print() {
        std::queue<int> temp = q;
        while (!temp.empty()) {
            std::cout << temp.front() << " ";
            temp.pop();
        }
        std::cout << std::endl;
    }
};

int main() {
    Queue myQueue;
    myQueue.enqueue(1);
    myQueue.enqueue(2);
    myQueue.enqueue(3);
    myQueue.enqueue(4);
    myQueue.enqueue(5);
    myQueue.enqueue(6);
    myQueue.enqueue(7);
    myQueue.enqueue(8);
    myQueue.enqueue(9);

    int k = 3;
    std::cout << "Original queue: ";
    myQueue.print();

    myQueue.reverseFirstK(k);

    std::cout << "Queue after flipping the first " << k << " elements: ";
    myQueue.print();

    return 0;
}
