#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 5

struct Student
{
    int id;
    char name[50];
    int age;
    float marks;
};

struct Student queue[MAX];

int front = -1;
int rear = -1;

int readInt(char message[])
{
    char input[100];
    char extra;
    int value;

    while (1)
    {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            exit(0);
        }

        if (sscanf(input, "%d %c", &value, &extra) == 1)
        {
            return value;
        }

        printf("Invalid input! Please enter a number.\n");
    }
}

float readFloat(char message[])
{
    char input[100];
    char extra;
    float value;

    while (1)
    {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            exit(0);
        }

        if (sscanf(input, "%f %c", &value, &extra) == 1)
        {
            return value;
        }

        printf("Invalid input! Please enter a valid number.\n");
    }
}

int validName(char name[])
{
    int i;

    if (strlen(name) == 0)
    {
        return 0;
    }

    for (i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }

    return 1;
}

void readName(char name[], int size)
{
    while (1)
    {
        if (fgets(name, size, stdin) == NULL)
        {
            exit(0);
        }

        name[strcspn(name, "\n")] = '\0';

        if (validName(name))
        {
            return;
        }

        printf("Invalid name! Name should contain only alphabets and spaces.\n");
        printf("Enter name again: ");
    }
}

int idExists(int searchID)
{
    int i;

    if (front == -1)
    {
        return 0;
    }

    for (i = front; i <= rear; i++)
    {
        if (queue[i].id == searchID)
        {
            return 1;
        }
    }

    return 0;
}

int readID()
{
    int id;

    while (1)
    {
        id = readInt("Enter Student ID: ");

        if (id <= 0)
        {
            printf("ID must be greater than 0!\n");
        }
        else if (idExists(id))
        {
            printf("ID already exists! Enter a different ID.\n");
        }
        else
        {
            return id;
        }
    }
}

int readAge()
{
    int age;

    while (1)
    {
        age = readInt("Enter Age: ");

        if (age < 5 || age > 100)
        {
            printf("Invalid age! Age must be between 5 and 100.\n");
        }
        else
        {
            return age;
        }
    }
}

float readMarks()
{
    float marks;

    while (1)
    {
        marks = readFloat("Enter Marks: ");

        if (marks < 0 || marks > 100)
        {
            printf("Invalid marks! Marks must be between 0 and 100.\n");
        }
        else
        {
            return marks;
        }
    }
}

void enqueue()
{
    struct Student s;

    if (rear == MAX - 1)
    {
        printf("\nQueue is FULL!\n");
        return;
    }

    s.id = readID();

    printf("Enter Student Name: ");
    readName(s.name, sizeof(s.name));

    s.age = readAge();

    s.marks = readMarks();

    if (front == -1)
    {
        front = 0;
    }

    rear++;

    queue[rear] = s;

    printf("\nStudent added successfully!\n");
}

void display()
{
    int i;

    if (front == -1 || front > rear)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    printf("\n===== STUDENT RECORDS =====\n");

    printf("ID\tName\t\tAge\tMarks\n");
    printf("--------------------------------------\n");

    for (i = front; i <= rear; i++)
    {
        printf("%d\t%-15s\t%d\t%.2f\n",
               queue[i].id,
               queue[i].name,
               queue[i].age,
               queue[i].marks);
    }
}

void update()
{
    int search;
    int found = 0;
    int i;

    if (front == -1 || front > rear)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    search = readInt("Enter ID to Update: ");

    for (i = front; i <= rear; i++)
    {
        if (queue[i].id == search)
        {
            printf("\nStudent found!\n");
            printf("Current Name: %s\n", queue[i].name);
            printf("Current Age: %d\n", queue[i].age);
            printf("Current Marks: %.2f\n", queue[i].marks);

            printf("\nEnter new name: ");
            readName(queue[i].name, sizeof(queue[i].name));

            queue[i].age = readAge();

            queue[i].marks = readMarks();

            found = 1;

            printf("\nStudent updated successfully!\n");

            break;
        }
    }

    if (!found)
    {
        printf("\nID not found! No record was updated.\n");
    }
}

void dequeue()
{
    if (front == -1 || front > rear)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    printf("\nDeleted Student:\n");
    printf("ID    : %d\n", queue[front].id);
    printf("Name  : %s\n", queue[front].name);
    printf("Age   : %d\n", queue[front].age);
    printf("Marks : %.2f\n", queue[front].marks);

    front++;

    if (front > rear)
    {
        front = -1;
        rear = -1;
    }

    printf("Student deleted successfully!\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n===== STUDENT QUEUE CRUD =====\n");

        printf("1. Create / Enqueue\n");
        printf("2. Read / Display\n");
        printf("3. Update\n");
        printf("4. Delete / Dequeue\n");
        printf("5. Exit\n");

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:
                enqueue();
                break;

            case 2:
                display();
                break;

            case 3:
                update();
                break;

            case 4:
                dequeue();
                break;

            case 5:
                printf("\nThank you!\n");
                exit(0);

            default:
                printf("Invalid choice! Please enter a number from 1 to 5.\n");
        }
    }

    return 0;
}