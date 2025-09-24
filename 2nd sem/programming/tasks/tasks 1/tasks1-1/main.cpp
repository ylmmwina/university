#include <iostream>

// завдання 1

using namespace std;

int findUniqueNumber(int arr[], int size) {
    int unique = 0;
    for (int i = 0; i < size; i++) {
        unique ^= arr[i]; // XOR усіх чисел(однакові числа знищують один одного а^a=0; a^0=a)
    }
    return unique;
}

int main() {
    int arr[] = {4, 1, 2, 1, 2, 4, 7}; // тільки 7 зустрічається один раз
    int size = sizeof(arr) / sizeof(arr[0]); // знаходимо розмір масиву

    cout << "Unique number: " << findUniqueNumber(arr, size) << endl;
    return 0;
}
