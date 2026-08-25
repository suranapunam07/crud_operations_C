#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Student
{
    int id;
    char name[50];
    float marks;
    struct Student *next;
};

struct Student *front = NULL;
struct Student *rear = NULL;


// ================= READ INTEGER =================

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


// ================= READ FLOAT =================

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


// ================= VALIDATE NAME =================

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


// ================= READ NAME =================

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


// ================= CHECK ID EXISTS =================

int idExists(int searchID)
{
    struct Student *temp = front;

    while (temp != NULL)
    {
        if (temp->id == searchID)
        {
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}


// ================= READ ID =================

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


// ================= READ MARKS =================

float readMarks()
{
    float marks;

    while (1)
    {
        marks = readFloat("Enter Student Marks: ");

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


// ================= ENQUEUE =================

void enqueue()
{
    struct Student *newNode;

    newNode = (struct Student *)malloc(sizeof(struct Student));

    if (newNode == NULL)
    {
        printf("Unable to allocate memory!\n");
        return;
    }

    newNode->id = readID();

    printf("Enter Student Name: ");
    readName(newNode->name, sizeof(newNode->name));

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

    printf("\nStudent added successfully!\n");
}


// ================= READ QUEUE =================

void readQueue()
{
    struct Student *temp;

    if (front == NULL)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    temp = front;

    printf("\n========== STUDENT QUEUE ==========\n");

    while (temp != NULL)
    {
        printf("ID: %d | Name: %s | Marks: %.2f\n",
               temp->id,
               temp->name,
               temp->marks);

        temp = temp->next;
    }

    printf("\nStudents queue displayed successfully!\n");
}


// ================= DEQUEUE =================

void dequeue()
{
    struct Student *temp;

    if (front == NULL)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    temp = front;

    printf("\nDeleted Student:\n");
    printf("ID: %d\n", temp->id);
    printf("Name: %s\n", temp->name);
    printf("Marks: %.2f\n", temp->marks);

    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);

    printf("\nStudent deleted successfully!\n");
}


// ================= UPDATE =================

void updateStudent()
{
    int id;
    struct Student *temp;

    if (front == NULL)
    {
        printf("\nQueue is empty!\n");
        return;
    }

    id = readInt("Enter the ID of the student to update: ");

    temp = front;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            printf("\nStudent found!\n");
            printf("Current Name: %s\n", temp->name);
            printf("Current Marks: %.2f\n", temp->marks);

            printf("\nEnter new name: ");
            readName(temp->name, sizeof(temp->name));

            temp->marks = readMarks();

            printf("\nStudent updated successfully!\n");

            return;
        }

        temp = temp->next;
    }

    printf("\nStudent not found!\n");
}


// ================= MAIN =================

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n========== STUDENT QUEUE CRUD ==========\n");

        printf("1. Create Student\n");
        printf("2. Read Queue\n");
        printf("3. Delete Student\n");
        printf("4. Update Student\n");
        printf("5. Exit\n");

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
                printf("\nProgram exited.\n");
                return 0;

            default:
                printf("Invalid choice! Please enter a number from 1 to 5.\n");
        }
    }

    return 0;
}