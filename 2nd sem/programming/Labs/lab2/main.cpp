#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Node {
    double data;
    Node* next;
    Node* prev;
    Node(double val) : data(val), next(nullptr), prev(nullptr) {}
};

// черга на базі двозв’язного циклічного списку
class Queue {
private:
    Node* head;
public:
    Queue() : head(nullptr) {}

    void push(double val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    double front() {
        return head ? head->data : 0;
    }

    void pop() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node* tail = head->prev;
            Node* newHead = head->next;
            tail->next = newHead;
            newHead->prev = tail;
            delete head;
            head = newHead;
        }
    }

    ~Queue() {
        while (!empty()) pop();
    }
};

// клас для розділення чисел на підмножини в одному масиві
class PartitionedList {
private:
    double* array;
    int size;
    int leftIndex, rightIndex, leftStart, rightStart;

    // якщо масив переповнюється, то він збільшується вдвічі
    void resize() {
        int newSize = size * 2;
        double* newArray = new double[newSize];

        int newLeftStart = newSize / 4;
        int newRightStart = newSize - newLeftStart;

        for (int i = leftIndex, j = newLeftStart; i < leftStart; ++i, ++j) {
            newArray[j] = array[i];
        }
        for (int i = rightStart, j = newRightStart; i <= rightIndex; ++i, ++j) {
            newArray[j] = array[i];
        }

        delete[] array;
        array = newArray;
        size = newSize;
        leftIndex = newLeftStart;
        leftStart = newLeftStart;
        rightIndex = newRightStart - 1;
        rightStart = newRightStart;
    }

public:
    PartitionedList(int initialSize, int offset)
        : size(initialSize), leftIndex(offset), rightIndex(initialSize - offset - 1), leftStart(offset), rightStart(initialSize - offset) {
        array = new double[size];
    }

    void pushLeft(double val) {
        if (leftIndex == 0) resize();
        array[--leftIndex] = val;
    }

    void pushRight(double val) {
        if (rightIndex == size - 1) resize();
        array[++rightIndex] = val;
    }

    void print(bool isLeft = true) {
        if (isLeft) {
            cout << "Elements of subset A: ";
            for (int i = leftIndex; i < leftStart; ++i) {
                cout << array[i] << " ";
            }
        } else {
            cout << "Elements of subset B: ";
            for (int i = rightStart; i <= rightIndex; ++i) {
                cout << array[i] << " ";
            }
        }
        cout << endl;
    }

    ~PartitionedList() {
        delete[] array;
    }
};

// функція перевіряє чи є число дільником n
bool condition(double num, int n, bool (*extraCondition)(int, int)) {
    int numInt = static_cast<int>(num);
    return (numInt > 0) && (numInt < n) && (n % numInt == 0) && extraCondition(numInt, n);
}

bool isEven(int num, int n) {
    return num % 2 == 0;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "File not found or could not be opened!" << endl;
        return 1;
    }

    int n;
    inputFile >> n; 
    cout << "N = " << n << endl;

    Queue queue;
    double number;
    while (inputFile >> number) {
        queue.push(number);
    }
    inputFile.close();

    PartitionedList list(100, 20);

    while (!queue.empty()) {
        double val = queue.front();
        queue.pop();
        if (condition(val, n, isEven)) {
            list.pushLeft(val);
        } else {
            list.pushRight(val);
        }
    }

    list.print(true);
    list.print(false);

    return 0;
}
