void removeDuplicates(int* arr, int* n) {
    int i, j = 0;
    for (i = 1; i < *n; i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }
    *n = j + 1;
}
