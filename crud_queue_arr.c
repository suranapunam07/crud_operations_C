#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX 5

struct Student
{
    unsigned int id;
    char name[50];
    int age;
    float marks;
};

struct Student queue[MAX];

int front = -1;
int rear = -1;
int idExists(unsigned int searchID)
{
    if (front == -1)
        return 0;
    for (int i = front; i <= rear; i++)
    {
        if (queue[i].id == searchID)
            return 1;
    }
    return 0;
}

int readInt(char message[])
{
    int value;
    char ch;
    while (1)
    {
        printf("%s", message);
        if (scanf("%d", &value) != 1)
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }

        ch = getchar();
        if (ch != '\n')
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }
        return value;
    }
}

float readFloat(char message[])
{
    float value;
    char ch;

    while (1)
    {
        printf("%s", message);
        if (scanf("%f", &value) != 1)
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }

        ch = getchar();
        if (ch != '\n')
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }
        return value;
    }
}

int validName(char name[])
{
    if (strlen(name) == 0)
        return 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
            return 0;
    }
    return 1;
}

void readName(char name[])
{
    while (1)
    {
        printf("Enter Student Name: ");

        if (scanf(" %49[^\n]", name) != 1)
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }

        if (validName(name))
        {
            while (getchar() != '\n');
            return;
        }

        printf("Invalid\n");
        while (getchar() != '\n');
    }
}

unsigned int readID()
{
    unsigned long int tempID;
    unsigned int id;
    char ch;

    while (1)
    {
        printf("Enter Student ID: ");
        if (scanf("%lu", &tempID) != 1)
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }

        ch = getchar();
        if (ch != '\n')
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }

        if (tempID > UINT_MAX)
        {
            printf("Invalid\n");
            continue;
        }

        if (tempID == 0)
        {
            printf("Invalid\n");
            continue;
        }

        id = (unsigned int)tempID;
        if (idExists(id))
        {
            printf("ID already exists. Invalid\n");
            continue;
        }
        return id;
    }
}

unsigned int readSearchID(char message[])
{
    unsigned long int tempID;
    unsigned int id;
    char ch;

    while (1)
    {
        printf("%s", message);

        if (scanf("%lu", &tempID) != 1)
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }

        ch = getchar();
        if (ch != '\n')
        {
            printf("Invalid\n");
            while (getchar() != '\n');
            continue;
        }

        if (tempID > UINT_MAX)
        {
            printf("Invalid\n");
            continue;
        }

        if (tempID == 0)
        {
            printf("Invalid\n");
            continue;
        }
        id = (unsigned int)tempID;
        return id;
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
            printf("Invalid\n");
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
            printf("Invalid\n");
        }
        else
        {
            return marks;
        }
    }
}

void enqueue()
{
    if (rear == MAX - 1)
    {
        printf("Queue is full!\n");
        return;
    }

    struct Student s;
    s.id = readID();
    readName(s.name);
    s.age = readAge();
    s.marks = readMarks();
    if (front == -1)
        front = 0;
    rear++;
    queue[rear] = s;
    printf("Student Added Successfully!\n");
}

void display()
{
    if (front == -1 || front > rear)
    {
        printf("Queue is empty!\n");
        return;
    }

    printf("\n");
    printf("          STUDENT QUEUE\n");
    printf("====================================\n");

    for (int i = front; i <= rear; i++)
    {
        printf("\nStudent %d\n", i+1);
        printf("ID     : %u\n", queue[i].id);
        printf("Name   : %s\n", queue[i].name);
        printf("Age    : %d\n", queue[i].age);
        printf("Marks  : %.2f\n", queue[i].marks);;
    }
}

void update()
{
    if (front == -1 || front > rear)
    {
        printf("Queue is empty!\n");
        return;
    }
    unsigned int search;
    search = readSearchID("Enter ID to Update: ");
    int found = 0;
    for (int i = front; i <= rear; i++)
    {
        if (queue[i].id == search)
        {
            printf("\nEnter new details:\n");

            readName(queue[i].name);

            queue[i].age = readAge();

            queue[i].marks = readMarks();

            found = 1;

            printf("Student Updated Successfully!\n");

            break;
        }
    }

    if (!found)
    {
        printf("Student ID not found!\n");
    }
}

void dequeue()
{
    if (front == -1 || front > rear)
    {
        printf("Queue is empty!\n");
        return;
    }

    printf("\nDeleted Student:\n");
  
    // printf("ID     : %u\n", queue[front].id);
    // printf("Name   : %s\n", queue[front].name);
    // printf("Age    : %d\n", queue[front].age);
    // printf("Marks  : %.2f\n", queue[front].marks);
    front++;
    if (front > rear)
    {
        front = -1;
        rear = -1;
    }
    printf("Student Deleted Successfully!\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("          STUDENT QUEUE CRUD\n");

        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        printf("\n");

        choice = readInt("Enter choice: ");

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
                printf("Program exited.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}