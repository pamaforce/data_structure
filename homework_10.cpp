#include <iostream>
#include <vector>
using namespace std;

// 直接插入排序
void directInsertSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 折半插入排序
void binaryInsertSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int left = 0, right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > key)
                right = mid - 1;
            else
                left = mid + 1;
        }
        for (int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }
        arr[left] = key;
    }
}

// 快速排序
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        cout << "当前轴位置: " << pivotIndex << ", 元素值: " << arr[pivotIndex] << endl;
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {1, 8, 6, 4, 10, 5, 3, 2, 22};

    cout << "直接插入排序:" << endl;
    vector<int> directInsertArr = arr;
    directInsertSort(directInsertArr);
    printArray(directInsertArr);

    cout << "\n折半插入排序:" << endl;
    vector<int> binaryInsertArr = arr;
    binaryInsertSort(binaryInsertArr);
    printArray(binaryInsertArr);

    cout << "\n快速排序:" << endl;
    vector<int> quickSortArr = arr;
    quickSort(quickSortArr, 0, quickSortArr.size() - 1);
    printArray(quickSortArr);

    return 0;
}
