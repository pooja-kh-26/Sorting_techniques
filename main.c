#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

void printArray(int arr[], int size);
void selectionSort(int arr[], int size);
void bubbleSort(int arr[], int size);
void mergeSort(int arr[], int l, int r);
void quickSort(int arr[], int low, int high);
void merge(int arr[], int p, int q, int r);
int partition(int array[], int low, int high);

size_t memoryUsed = 0; // Global variable to track memory usage
int maxRecursionDepth = 0; // Global variable to track maximum recursion depth
int currentRecursionDepth = 0; // Global variable to track current recursion depth

int main() {
    int size, choice;

    // Prompt the user to enter the size of the array
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    // Allocate memory for the array
    int *data = (int *)malloc(size * sizeof(int));
    int *originalData = (int *)malloc(size * sizeof(int)); // To reset data for each sort

    // Prompt the user to enter the elements of the array
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &data[i]);
        originalData[i] = data[i]; // Copy original data
    }

    // Printing unsorted array
    printf("\nUnsorted Array\n");
    printArray(data, size);

    LARGE_INTEGER frequency, start, end;
    double elapsed_ns;

    do {
        // Prompt user to choose a sorting method
        printf("\nChoose sorting method:\n");
        printf("1. Selection Sort\n");
        printf("2. Bubble Sort\n");
        printf("3. Merge Sort\n");
        printf("4. Quick Sort\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        memoryUsed = 0; // Reset memory used before each sort
        maxRecursionDepth = 0; // Reset max recursion depth before each sort
        currentRecursionDepth = 0; // Reset current recursion depth before each sort

        switch (choice) {
            case 1:
                for (int i = 0; i < size; i++) data[i] = originalData[i]; // Reset data
                QueryPerformanceFrequency(&frequency);
                QueryPerformanceCounter(&start);
                selectionSort(data, size);
                QueryPerformanceCounter(&end);
                elapsed_ns = (double)(end.QuadPart - start.QuadPart) * 1e9 / frequency.QuadPart;
                printf("\nSorted array in Ascending Order using Selection Sort\n");
                printArray(data, size);
                printf("\nTime taken: %.0f nanoseconds\n", elapsed_ns);
                printf("Space complexity: %zu bytes\n", sizeof(int));
                break;
            case 2:
                for (int i = 0; i < size; i++) data[i] = originalData[i]; // Reset data
                QueryPerformanceFrequency(&frequency);
                QueryPerformanceCounter(&start);
                bubbleSort(data, size);
                QueryPerformanceCounter(&end);
                elapsed_ns = (double)(end.QuadPart - start.QuadPart) * 1e9 / frequency.QuadPart;
                printf("\nSorted array in Ascending Order using Bubble Sort\n");
                printArray(data, size);
                printf("\nTime taken: %.0f nanoseconds\n", elapsed_ns);
                printf("Space complexity: %zu bytes\n", sizeof(int));
                break;
            case 3:
                for (int i = 0; i < size; i++) data[i] = originalData[i]; // Reset data
                QueryPerformanceFrequency(&frequency);
                QueryPerformanceCounter(&start);
                mergeSort(data, 0, size - 1);
                QueryPerformanceCounter(&end);
                elapsed_ns = (double)(end.QuadPart - start.QuadPart) * 1e9 / frequency.QuadPart;
                printf("\nSorted array in Ascending Order using Merge Sort\n");
                printArray(data, size);
                printf("\nTime taken: %.0f nanoseconds\n", elapsed_ns);
                printf("Space complexity: %zu bytes\n", memoryUsed + size * sizeof(int));
                break;
            case 4:
                for (int i = 0; i < size; i++) data[i] = originalData[i]; // Reset data
                QueryPerformanceFrequency(&frequency);
                QueryPerformanceCounter(&start);
                quickSort(data, 0, size - 1);
                QueryPerformanceCounter(&end);
                elapsed_ns = (double)(end.QuadPart - start.QuadPart) * 1e9 / frequency.QuadPart;
                printf("\nSorted array in Ascending Order using Quick Sort\n");
                printArray(data, size);
                printf("\nTime taken: %.0f nanoseconds\n", elapsed_ns);
                printf("Space complexity: %zu bytes\n", sizeof(int) * (1 + maxRecursionDepth));
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    // Free the allocated memory
    free(data);
    free(originalData);
    return 0;
}

// Function to print an array
void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

// Function to swap the position of two elements - used in Selection Sort and Quick Sort
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Selection sort
void selectionSort(int array[], int size) {
    for (int step = 0; step < size - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < size; i++) {
            if (array[i] < array[min_idx])
                min_idx = i;
        }
        swap(&array[min_idx], &array[step]);
    }
}

// Bubble sort
void bubbleSort(int array[], int size) {
    for (int step = 0; step < size - 1; ++step) {
        for (int i = 0; i < size - step - 1; ++i) {
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
            }
        }
    }
}

// Merge Sort
void merge(int arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *M = (int *)malloc(n2 * sizeof(int));

    memoryUsed += n1 * sizeof(int) + n2 * sizeof(int); // Track memory used for temporary arrays

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }

    free(L);
    free(M);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick sort
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        // Update the maximum recursion depth
        currentRecursionDepth++;
        if (currentRecursionDepth > maxRecursionDepth) {
            maxRecursionDepth = currentRecursionDepth;
        }

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);

        // Decrement the current recursion depth
        currentRecursionDepth--;
    }
    // Calculate the maximum recursion depth to estimate stack space used
    if (low == 0 && high == sizeof(array) / sizeof(array[0]) - 1) {
        memoryUsed += sizeof(int) * (1 + maxRecursionDepth); // Recursive call stack
    }
}
