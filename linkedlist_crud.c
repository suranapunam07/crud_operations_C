#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Student
{
    int Id;
    char Name[50];
    int Age;
    float Marks;
    struct Student *next;
};

struct Student *head = NULL;

int isValidName(char name[])
{
    int i;

    if (strlen(name) == 0)
        return 0;

    for (i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
            return 0;
    }

    return 1;
}

int isIdExists(int id)
{
    struct Student *temp = head;

    while (temp != NULL)
    {
        if (temp->Id == id)
            return 1;

        temp = temp->next;
    }

    return 0;
}

int getValidId()
{
    int id;

    while (1)
    {
        printf("Enter the student Roll No: ");

        if (scanf("%d", &id) != 1)
        {
            printf("Invalid input! Roll No must be a number.\n");
            while (getchar() != '\n');
        }
        else if (id <= 0)
        {
            printf("Roll No must be greater than 0.\n");
        }
        else if (isIdExists(id))
        {
            printf("Roll No already exists!\n");
        }
        else
        {
            return id;
        }
    }
}

void getValidName(char name[])
{
    while (1)
    {
        printf("Enter the student name: ");
        scanf(" %[^\n]", name);

        if (isValidName(name))
            return;

        printf("Invalid name! Use only alphabets and spaces.\n");
    }
}

int getValidAge()
{
    int age;

    while (1)
    {
        printf("Enter the student age: ");

        if (scanf("%d", &age) != 1)
        {
            printf("Invalid input! Age must be a number.\n");
            while (getchar() != '\n');
        }
        else if (age < 1 || age > 100)
        {
            printf("Age must be between 1 and 100.\n");
        }
        else
        {
            return age;
        }
    }
}

float getValidMarks()
{
    float marks;

    while (1)
    {
        printf("Enter the student's marks: ");

        if (scanf("%f", &marks) != 1)
        {
            printf("Invalid input! Marks must be a number.\n");
            while (getchar() != '\n');
        }
        else if (marks < 0 || marks > 100)
        {
            printf("Marks must be between 0 and 100.\n");
        }
        else
        {
            return marks;
        }
    }
}

void CreateStudent()
{
    struct Student *newNode;

    newNode = (struct Student *)malloc(sizeof(struct Student));

    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    newNode->Id = getValidId();
    getValidName(newNode->Name);
    newNode->Age = getValidAge();
    newNode->Marks = getValidMarks();

    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        struct Student *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    printf("\nStudent added successfully!\n");
}

void ReadStudent()
{
    struct Student *temp;

    if (head == NULL)
    {
        printf("\nLinked List is Empty!\n");
        return;
    }

    temp = head;

    printf("\n========== STUDENT RECORDS ==========\n");

    while (temp != NULL)
    {
        printf("\nStudent Roll No : %d", temp->Id);
        printf("\nStudent Name    : %s", temp->Name);
        printf("\nStudent Age     : %d", temp->Age);
        printf("\nStudent Marks   : %.2f", temp->Marks);
        printf("\n-------------------------------------\n");

        temp = temp->next;
    }
}

void updateStudent()
{
    int id;
    int found = 0;

    struct Student *temp = head;

    if (head == NULL)
    {
        printf("\nLinked List is Empty!\n");
        return;
    }

    printf("\nEnter the Roll No to update: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid Roll No!\n");
        while (getchar() != '\n');
        return;
    }

    if (id <= 0)
    {
        printf("Roll No must be greater than 0.\n");
        return;
    }

    while (temp != NULL)
    {
        if (temp->Id == id)
        {
            getValidName(temp->Name);
            temp->Age = getValidAge();
            temp->Marks = getValidMarks();

            found = 1;

            printf("\nStudent record updated successfully!\n");
            break;
        }

        temp = temp->next;
    }

    if (found == 0)
    {
        printf("\nStudent not found!\n");
    }
}

void deleteStudent()
{
    int id;

    struct Student *temp;
    struct Student *prev;

    if (head == NULL)
    {
        printf("\nLinked List is Empty!\n");
        return;
    }

    printf("\nEnter the Roll No to delete: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid Roll No!\n");
        while (getchar() != '\n');
        return;
    }

    if (id <= 0)
    {
        printf("Roll No must be greater than 0.\n");
        return;
    }

    if (head->Id == id)
    {
        temp = head;
        head = head->next;
        free(temp);

        printf("\nRecord Deleted Successfully!\n");
        return;
    }

    prev = head;
    temp = head->next;

    while (temp != NULL)
    {
        if (temp->Id == id)
        {
            prev->next = temp->next;
            free(temp);

            printf("\nRecord Deleted Successfully!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nStudent not found!\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("\n========== STUDENT MANAGEMENT ==========\n");

        printf("\n1. Create");
        printf("\n2. Read");
        printf("\n3. Update");
        printf("\n4. Delete");
        printf("\n5. Exit");

        printf("\n\nEnter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                CreateStudent();
                break;

            case 2:
                ReadStudent();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                printf("\nProgram exited.\n");
                return 0;

            default:
                printf("\nInvalid choice! Please enter 1-5.\n");
        }
    }

    return 0;
}