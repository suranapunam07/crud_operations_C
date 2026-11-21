
#include <stdio.h>
#define MAX 100
#define MAX_ATTEMPTS 3

int readInteger(int *value)
{
    int result;
    int ch;

    result = scanf("%d", value);

    if (result == 1)
    {
        ch = getchar();

        if (ch == '\n')
            return 1;

        while (ch != '\n' && ch != EOF)
            ch = getchar();

        return 0;
    }

    while ((ch = getchar()) != '\n' && ch != EOF);

    return 0;
}

int getValidInteger(int *value)
{
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        if (readInteger(value))
            return 1;

        attempts++;
        printf("Invalid input! Enter an integer: ");
    }

    printf("\nMaximum attempts reached!\n");
    return 0;
}

int isDuplicate(int arr[], int n, int value)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (arr[i] == value)
            return 1;
    }

    return 0;
}

int linear_search(int arr[], int n, int target)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (arr[i] == target)
            return i;
    }

    return -1;
}

int binary_search(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;

        else if (arr[mid] < target)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}

int isSorted(int arr[], int n)
{
    int i;

    for (i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            return 0;
    }

    return 1;
}

void display_array(int arr[], int n)
{
    int i;

    printf("Array: ");

    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

// UPDATE
void update(int arr[], int n)
{
    int oldValue, newValue;
    int i;

    printf("Enter element to update: ");

    if (!getValidInteger(&oldValue))
        return;

    for (i = 0; i < n; i++)
    {
        if (arr[i] == oldValue)
            break;
    }

    if (i == n)
    {
        printf("Element not found.\n");
        return;
    }

    printf("Enter new value: ");

    if (!getValidInteger(&newValue))
        return;

    if (isDuplicate(arr, n, newValue))
    {
        printf("Duplicate value not allowed!\n");
        return;
    }

    arr[i] = newValue;

    printf("Element updated successfully.\n");
}

//delete
int delete(int arr[], int n)
{
    int key, i;

    if (n == 0)
    {
        printf("Array is empty!\n");
        return n;
    }

    printf("Enter element to delete: ");

    if (!getValidInteger(&key))
        return n;

    for (i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            while (i < n - 1)
            {
                arr[i] = arr[i + 1];
                i++;
            }
            n--;
            printf("Element deleted successfully.\n");
            return n;
        }
    }

    printf("Element not found.\n");
    return n;
}


int main()
{
    int arr[MAX];
    int n, i, choice, key, result;
    int attempts;

    printf("===== SEARCHING MENU =====\n");

    printf("Enter number of elements (1-%d): ", MAX);

    if (!getValidInteger(&n))
        return 0;

    if (n < 1 || n > MAX)
    {
        printf("Invalid size! Size must be between 1 and %d.\n", MAX);
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        attempts = 0;

        while (attempts < MAX_ATTEMPTS)
        {
            printf("Enter element %d: ", i + 1);

            if (!readInteger(&arr[i]))
            {
                attempts++;
                printf("Invalid input! Enter an integer.\n");
                continue;
            }

            if (isDuplicate(arr, i, arr[i]))
            {
                attempts++;
                printf("Duplicate value! Enter a different integer.\n");
                continue;
            }

            break;
        }

        if (attempts == MAX_ATTEMPTS)
        {
            printf("Maximum attempts reached!\n");
            return 0;
        }
    }

    do
    {
        printf("\n===== SEARCHING MENU =====\n");
        printf("1. Linear Search\n");
        printf("2. Binary Search\n");
        printf("3. Display Array\n");
        printf("4. Update Element\n");
        printf("5. Delete Element\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");

        if (!getValidInteger(&choice))
            return 0;

        switch (choice)
        {
            case 1:
                display_array(arr, n);

                printf("Enter element to search: ");

                if (!getValidInteger(&key))
                    return 0;

                result = linear_search(arr, n, key);

                if (result != -1)
                    printf("Element found at position %d.\n", result + 1);
                else
                    printf("Element not found.\n");

                break;

            case 2:

                if (!isSorted(arr, n))
                {
                    printf("Array is not sorted.\n");
                    printf("Please enter elements in ascending order.\n");
                    break;
                }

                display_array(arr, n);

                printf("Enter element to search: ");

                if (!getValidInteger(&key))
                    return 0;

                result = binary_search(arr, n, key);

                if (result != -1)
                    printf("Element found at position %d.\n", result + 1);
                else
                    printf("Element not found.\n");

                break;

            case 3:
                display_array(arr, n);
                break;

            case 4:
                update(arr, n);
                break;

            case 5:
                n = delete(arr, n);
                break;

            case 6:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Enter 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}
