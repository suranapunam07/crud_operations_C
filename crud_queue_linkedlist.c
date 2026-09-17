#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

struct Student
{
    unsigned int id;
    char name[50];
    float marks;
    struct Student *next;
};

struct Student *front = NULL;
struct Student *rear = NULL;

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

int idExists(unsigned int searchID)
{
    struct Student *temp = front;

    while (temp != NULL)
    {
        if (temp->id == searchID)
            return 1;

        temp = temp->next;
    }

    return 0;
}

unsigned int readID()
{
    unsigned long long int tempID;
    unsigned int id;
    char ch;

    while (1)
    {
        printf("Enter Student ID: ");

        if (scanf("%llu", &tempID) != 1)
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
            printf("Invalid\n");
            continue;
        }

        return id;
    }
}

unsigned int readSearchID(char message[])
{
    unsigned long long int tempID;
    unsigned int id;
    char ch;

    while (1)
    {
        printf("%s", message);

        if (scanf("%llu", &tempID) != 1)
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

float readMarks()
{
    float marks;

    while (1)
    {
        marks = readFloat("Enter Student Marks: ");

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
    struct Student *newNode =
        (struct Student *)malloc(sizeof(struct Student));

    if (newNode == NULL)
    {
        printf("Invalid\n");
        return;
    }

    newNode->id = readID();

    printf("Enter Student Name: ");
    readName(newNode->name);

    newNode->marks = readMarks();

    newNode->next = NULL;

    if (rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    printf("Added!\n");
}

void readQueue()
{
    if (front == NULL)
    {
        printf("Invalid\n");
        return;
    }

    struct Student *temp = front;
    int studentNumber = 1;
    printf("\n");
    printf("          STUDENT QUEUE\n");
   
    while (temp != NULL)
    {
        printf("\nStudent %d\n", studentNumber);
        printf("ID     : %u\n", temp->id);
        printf("Name   : %s\n", temp->name);
        printf("Marks  : %.2f\n", temp->marks);
        printf("\n");

        temp = temp->next;
        studentNumber++;
    }
}

void dequeue()
{
    if (front == NULL)
    {
        printf("Invalid\n");
        return;
    }

    struct Student *temp = front;

    printf("\nDeleted Student:\n");
    printf("ID     : %u\n", temp->id);
    printf("Name   : %s\n", temp->name);
    printf("Marks  : %.2f\n", temp->marks);

    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);

    printf("Deleted!\n");
}

void updateStudent()
{
    if (front == NULL)
    {
        printf("Invalid\n");
        return;
    }

    unsigned int id =
        readSearchID("Enter ID to Update: ");

    struct Student *temp = front;

    int found = 0;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("Enter new name: ");
            readName(temp->name);

            temp->marks = readMarks();

            found = 1;

            printf("Updated!\n");

            break;
        }

        temp = temp->next;
    }

    if (!found)
        printf("Invalid\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("          STUDENT QUEUE CRUD\n");
        printf("====================================\n");

        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Delete\n");
        printf("4. Update\n");
        printf("5. Exit\n");

        printf("\n");

        choice = readInt("Enter choice: ");

        switch (choice)
        {
            case 1:
                enqueue();
                break;

            case 2:
                readQueue();
                break;

            case 3:
                dequeue();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                return 0;

            default:
                printf("Invalid\n");
        }
    }

    return 0;
}