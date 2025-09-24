#include <iostream>

using namespace std;

int compare(int* a, int* b) {
    return (*a > *b) - (*a < *b);
}

void insertionSort(int arr[], int n, int (*compare)(int*, int*)) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && compare(&arr[j], &key) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(int arr[], int n, int (*compare)(int*, int*)) {
    if (n <= 0) return;

    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int bucketCount = max(1, n / 5);
    int** buckets = new int*[bucketCount];
    int* bucketSizes = new int[bucketCount]{};

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        int bucketIndex = (arr[i] - minVal) * bucketCount / (maxVal - minVal + 1);
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        insertionSort(buckets[i], bucketSizes[i], compare);
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
        delete[] buckets[i];
    }

    delete[] buckets;
    delete[] bucketSizes;
}

int main() {
    int arr[] = {42, 32, 33, 52, 37, 47, 51};
    int n = sizeof(arr) / sizeof(arr[0]);

    bucketSort(arr, n, compare);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
