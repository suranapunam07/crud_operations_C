#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_ATTEMPTS 3

struct Student
{
    unsigned int Id;
    char Name[50];
    int Age;
    float Marks;
    struct Student *next;
};

struct Student *head = NULL;

int isIdExists(unsigned int id)
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

unsigned int getValidId()
{
    unsigned int id;
    unsigned long int tempId;
    int attempts = 0;
    char ch;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter ID: ");

        if (scanf("%lu", &tempId) != 1)
        {
            printf("Invalid\n");

            while (getchar() != '\n');

            attempts++;
        }
        else
        {
            ch = getchar();

            if (ch != '\n')
            {
                printf("Invalid\n");

                while (getchar() != '\n');

                attempts++;
            }
            else if (tempId > UINT_MAX)
            {
                printf("Invalid\n");
                attempts++;
            }
            else if (tempId == 0)
            {
                printf("Invalid\n");
                attempts++;
            }
            else
            {
                id = (unsigned int)tempId;

                if (isIdExists(id))
                {
                    printf("Invalid\n");
                    attempts++;
                }
                else
                {
                    return id;
                }
            }
        }
    }

    printf("Invalid\n");
    return 0;
}

int isValidName(char name[])
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

int getValidName(char name[])
{
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter Name: ");

        gets(name);

        if (isValidName(name))
            return 1;

        printf("Invalid\n");
        attempts++;
    }

    printf("Invalid\n");
    return 0;
}

int getValidAge()
{
    int age;
    int attempts = 0;
    char ch;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter Age: ");

        if (scanf("%d", &age) != 1)
        {
            printf("Invalid\n");

            while (getchar() != '\n');

            attempts++;
        }
        else
        {
            ch = getchar();

            if (ch != '\n')
            {
                printf("Invalid\n");

                while (getchar() != '\n');

                attempts++;
            }
            else if (age < 1 || age > 100)
            {
                printf("Invalid\n");
                attempts++;
            }
            else
            {
                return age;
            }
        }
    }

    printf("Invalid\n");
    return -1;
}

float getValidMarks()
{
    float marks;
    int attempts = 0;
    char ch;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter Marks: ");

        if (scanf("%f", &marks) != 1)
        {
            printf("Invalid\n");

            while (getchar() != '\n');

            attempts++;
        }
        else
        {
            ch = getchar();

            if (ch != '\n')
            {
                printf("Invalid\n");

                while (getchar() != '\n');

                attempts++;
            }
            else if (marks < 0 || marks > 100)
            {
                printf("Invalid\n");
                attempts++;
            }
            else
            {
                return marks;
            }
        }
    }

    printf("Invalid\n");
    return -1;
}

unsigned int getSearchId(char message[])
{
    unsigned int id;
    unsigned long int tempId;
    int attempts = 0;
    char ch;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("%s", message);

        if (scanf("%lu", &tempId) != 1)
        {
            printf("Invalid\n");

            while (getchar() != '\n');

            attempts++;
        }
        else
        {
            ch = getchar();

            if (ch != '\n')
            {
                printf("Invalid\n");

                while (getchar() != '\n');

                attempts++;
            }
            else if (tempId > UINT_MAX)
            {
                printf("Invalid\n");
                attempts++;
            }
            else if (tempId == 0)
            {
                printf("Invalid\n");
                attempts++;
            }
            else
            {
                id = (unsigned int)tempId;
                return id;
            }
        }
    }

    printf("Invalid\n");
    return 0;
}

void CreateStudent()
{
    struct Student *newNode;

    newNode = (struct Student *)malloc(sizeof(struct Student));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->Id = getValidId();

    if (newNode->Id == 0)
    {
        free(newNode);
        return;
    }

    //while (getchar() != '\n');

    if (!getValidName(newNode->Name))
    {
        free(newNode);
        return;
    }

    newNode->Age = getValidAge();

    if (newNode->Age == -1)
    {
        free(newNode);
        return;
    }

    newNode->Marks = getValidMarks();

    if (newNode->Marks == -1)
    {
        free(newNode);
        return;
    }

    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        struct Student *temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    printf("Added!\n");
}

void ReadStudent()
{
    struct Student *temp = head;

    if (head == NULL)
    {
        printf("No student records\n");
        return;
    }

    printf("\nSTUDENT RECORDS\n");

    while (temp != NULL)
    {
        printf("\nID      : %u", temp->Id);
        printf("\nName    : %s", temp->Name);
        printf("\nAge     : %d", temp->Age);
        printf("\nMarks   : %.2f\n", temp->Marks);

        temp = temp->next;
    }
}

void updateStudent()
{
    unsigned int id;
    struct Student *temp;

    if (head == NULL)
    {
        printf("No student records\n");
        return;
    }

    id = getSearchId("Enter ID to update: ");

    if (id == 0)
        return;

    temp = head;

    while (temp != NULL)
    {
        if (temp->Id == id)
        {
            while (getchar() != '\n');

            if (!getValidName(temp->Name))
                return;

            temp->Age = getValidAge();

            if (temp->Age == -1)
                return;

            temp->Marks = getValidMarks();

            if (temp->Marks == -1)
                return;

            printf("Updated!\n");
            return;
        }

        temp = temp->next;
    }

    printf("Invalid\n");
}

void deleteStudent()
{
    unsigned int id;
    struct Student *temp;
    struct Student *prev = NULL;

    if (head == NULL)
    {
        printf("No student records\n");
        return;
    }

    id = getSearchId("Enter ID to delete: ");

    if (id == 0)
        return;

    temp = head;

    while (temp != NULL)
    {
        if (temp->Id == id)
        {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);

            printf("Deleted!\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Invalid\n");
}

int main()
{
    int choice;
    int attempts;
    char ch;

    while (1)
    {
        printf("\nSTUDENT MANAGEMENT\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        attempts = 0;

        while (attempts < MAX_ATTEMPTS)
        {
            printf("Enter choice: ");

            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid\n");

                while (getchar() != '\n');

                attempts++;
            }
            else
            {
                ch = getchar();

                if (ch != '\n')
                {
                    printf("Invalid\n");

                    while (getchar() != '\n');

                    attempts++;
                }
                else if (choice < 1 || choice > 5)
                {
                    printf("Invalid\n");
                    attempts++;
                }
                else
                {
                    break;
                }
            }
        }

        if (attempts == MAX_ATTEMPTS)
        {
            printf("Invalid\n");
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
                return 0;
        }
    }
}