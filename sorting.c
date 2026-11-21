
#include <stdio.h>

#define MAX 100

// 1. Bubble Sort
//The largest element moves to the last position after every pass.
void bubbleSort(int arr[], int n)
{
    int swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}

// 2. Selection Sort
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// 3. Insertion Sort
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. Merge Sort - Merge Function
//Divide: Divide the array into smaller halves until each part contains only one element.
//Merge: Combine those smaller parts in sorted order.

void merge(int arr[], int temp[], int start, int mid, int end)
{
    int i = start;
    int j = mid + 1;
    int k = start;

    while (i <= mid && j <= end)
    {
        if (arr[i] < arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }
    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= end)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (int i = start; i <= end; i++)
    {
        arr[i] = temp[i];
    }
}

// Merge Sort 
void mergeSort(int arr[], int temp[], int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;

        mergeSort(arr, temp, start, mid);
        mergeSort(arr, temp, mid + 1, end);

        merge(arr, temp, start, mid, end);
    }
}

// 5. Quick Sort - Partition Function
//Partition the array so that smaller elements come before the pivot and larger elements come after it.
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int st, int end)
{
    int pivot = arr[end];
    int i = st - 1;
    int j;

    for (j = st; j < end; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[end]);

    return i + 1;
}

void quickSort(int arr[], int st, int end)
{
    if (st < end)
    {
        int pivotIndex = partition(arr, st, end);

        quickSort(arr, st, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, end);
    }
}

//display array
void display(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

// Main Function
int main()
{
    int arr[MAX], temp[MAX];
    int n, choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid array size!");
        return 0;
    }

    printf("Enter array elements: ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\n----- SORTING MENU -----\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Merge Sort\n");
    printf("5. Quick Sort\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            bubbleSort(arr, n);
            break;

        case 2:
            selectionSort(arr, n);
            break;

        case 3:
            insertionSort(arr, n);
            break;

        case 4:
            mergeSort(arr, temp, 0, n - 1);
            break;

        case 5:
            quickSort(arr, 0, n - 1);
            break;

        default:
            printf("Invalid choice!");
            return 0;
    }

    printf("\nSorted Array: ");
    display(arr, n);

    return 0;
}
