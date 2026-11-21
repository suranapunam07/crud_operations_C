#include <stdio.h>
#include <limits.h>
#define MAX 20

int heap[MAX];
int size = 0;
int isMaxHeap = 1;

int readInput(int *value)
{
    int ch;
    int valid = 1;

    if (scanf("%d", value) != 1)
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }

        return 0;
    }
    ch = getchar();

    while (ch != '\n' && ch != EOF)
    {
        if (ch != ' ' && ch != '\t' && ch != '\r')
        {
            valid = 0;
        }

        ch = getchar();
    }
    return valid;
}

int isHeapFull()
{
    return size == MAX;
}

int isHeapEmpty()
{
    return size == 0;
}

int searchElement(int value)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (heap[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int hasPriority(int a, int b)
{
    if (isMaxHeap)
    {
        return a > b;
    }

    return a < b;
}

void heap_up(int index)
{
    int parent;

    while (index > 0)
    {
        parent = (index - 1) / 2;
        if (hasPriority(heap[index], heap[parent]))
        {
            swap(&heap[index], &heap[parent]);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void heap_down(int index)
{
    int pos;
    int left;
    int right;

    while (1)
    {
        pos = index;

        left = 2 * index + 1;
        right = 2 * index + 2;

        if (left < size &&
            hasPriority(heap[left], heap[pos]))
        {
            pos = left;
        }

        if (right < size &&
            hasPriority(heap[right], heap[pos]))
        {
            pos = right;
        }

        if (pos != index)
        {
            swap(&heap[index], &heap[pos]);
            index = pos;
        }
        else
        {
            break;
        }
    }
}

void create()
{
    int value;

    if (isHeapFull())
    {
        printf("Heap is full!\n");
        return;
    }

    printf("Enter element to insert: ");

    if (!readInput(&value))
    {
        printf("Invalid input! Enter an integer.\n");
        return;
    }

    if (searchElement(value) != -1)
    {
        printf("Duplicate element is not allowed!\n");
        return;
    }

    heap[size] = value;

    heap_up(size);

    size++;

    printf("Element inserted successfully.\n");
}

void read_heap()
{
    int i;

    if (isHeapEmpty())
    {
        printf("Heap is empty.\n");
        return;
    }

    if (isMaxHeap)
    {
        printf("Max Heap: ");
    }
    else
    {
        printf("Min Heap: ");
    }

    for (i = 0; i < size; i++)
    {
        printf("%d ", heap[i]);
    }

    printf("\n");
}

void update()
{
    int oldValue;
    int newValue;
    int index;

    if (isHeapEmpty())
    {
        printf("Heap is empty.\n");
        return;
    }

    printf("Enter element to update: ");

    if (!readInput(&oldValue))
    {
        printf("Invalid input! Enter an integer.\n");
        return;
    }

    index = searchElement(oldValue);

    if (index == -1)
    {
        printf("Element not found!\n");
        return;
    }

    printf("Enter new value: ");

    if (!readInput(&newValue))
    {
        printf("Invalid input! Enter an integer.\n");
        return;
    }

    if (newValue != oldValue &&
        searchElement(newValue) != -1)
    {
        printf("Duplicate element is not allowed!\n");
        return;
    }

    heap[index] = newValue;

    if (index > 0 &&
        hasPriority(heap[index],
                    heap[(index - 1) / 2]))
    {
        heap_up(index);
    }
    else
    {
        heap_down(index);
    }

    printf("Element updated successfully.\n");
}

void deleteElement()
{
    int value;
    int index;

    if (isHeapEmpty())
    {
        printf("Heap is empty.\n");
        return;
    }

    printf("Enter element to delete: ");

    if (!readInput(&value))
    {
        printf("Invalid input! Enter an integer.\n");
        return;
    }

    index = searchElement(value);

    if (index == -1)
    {
        printf("Element not found!\n");
        return;
    }

    heap[index] = heap[size - 1];

    size--;

    if (index < size)
    {
        if (index > 0 &&
            hasPriority(heap[index],
                        heap[(index - 1) / 2]))
        {
            heap_up(index);
        }
        else
        {
            heap_down(index);
        }
    }

    printf("Element deleted successfully.\n");
}

int main()
{
    int choice;
    int type;

    printf("Choose Heap Type:\n");
    printf("1. Max Heap\n");
    printf("2. Min Heap\n");
    printf("Enter your choice: ");

    if (!readInput(&type) || (type != 1 && type != 2))
    {
        printf("Invalid heap type!\n");
        return 0;
    }

    if (type == 1)
    {
        isMaxHeap = 1;
        printf("Max Heap selected.\n");
    }
    else
    {
        isMaxHeap = 0;
        printf("Min Heap selected.\n");
    }

    do
    {
        printf("\n--- HEAP CRUD MENU ---\n");
        printf("1. Create\n");
        printf("2. Read \n");
        printf("3. Update Element\n");
        printf("4. Delete Element\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");

        if (!readInput(&choice))
        {
            printf("Invalid input! Enter an integer.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                create();
                break;

            case 2:
                read_heap();
                break;

            case 3:
                update();
                break;

            case 4:
                deleteElement();
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}