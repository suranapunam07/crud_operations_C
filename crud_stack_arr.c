#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 5

struct Student
{
    int id;
    char name[50];
    float marks;
};

struct Student stack[MAX];

int top = -1;

int readInt(char message[])
{
    char input[100];
    char extra;
    int value;

    while(1)
{
    printf("%s",message);
    if(fgets(input,sizeof(input),stdin) == NULL)
    {
        exit(0);
    }
    if(sscanf(input,"%d %c",&value, &extra) == 1)
    {
        return value;
    }
    printf("Invalid Input! Please enter a number.\n");
}
}

float readFloat(char message[])
{
    char input[100];
    char extra;
    float value;

    while(1)
    {
        printf("%s",message);
        if(fgets(input,sizeof(input),stdin) == NULL)
        {
            exit(0);
        }
        if(sscanf(input,"%f %c",&value,&extra)==1)
        {
            return value;
        }
        printf("Invalid Input! Please enter a number.\n");
    }
}

int validName(char name[])
{
    int i;

    if(strlen(name) == 0)
    {
        return 0;
    }
    for(i = 0; name[i] != '\0';i++)
    {
        if(!isalpha((unsigned char)name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

void readName(char name[], int size)
{
    while(1)
    {
        if(fgets(name,size,stdin) == NULL)
        {
            exit(0);
        }

        name[strcspn(name, "\n")] = '\0';

        if(validName(name))
        {
            return;
        }
        printf("Invalid Input! Please enter a valid name.\n");
    }
}

int idExists(int searchID)
{
    int i;
    for(i = 0; i <= top; i++)
    {
        if(stack[i].id == searchID)
        {
            return 1;
        }
    }
    return 0;
}

int readID()
{
    int id;
    while(1)
    {
        id = readInt("Enter Student ID: ");

        if(id <= 0)
        {
            printf("ID must be greater than 0");
        }
        else if(idExists(id))
        {
            printf("ID already exists.");
        }
        else
        {
            return id;
        }
    }
}

float readMarks()
{
    float marks;
    while(1)
    {
        marks = readFloat("Enter Student Marks:");

        if(marks < 0 || marks > 100)
        {
            printf("Marks must be between 0 and 100.\n");
        }
        else
        {
            return marks;
        }
    }
}

void push()
{
    struct Student s;

    if (top == MAX - 1)
    {
        printf("\nStack is FULL!\n");
        return;
    }

    s.id = readID();

    printf("Enter Student Name: ");
    readName(s.name, sizeof(s.name));

    s.marks = readMarks();

    top++;

    stack[top] = s;

    printf("\nStudent added successfully!\n");
}

void display()
{
    int i;

    if (top == -1)
    {
        printf("\nStack is empty!\n");
        return;
    }

    printf("\n*** STUDENT STACK ***\n");

    for (i = top; i >= 0; i--)
    {
        printf("ID: %d | Name: %s | Marks: %.2f\n",
               stack[i].id,
               stack[i].name,
               stack[i].marks);
    }

    printf("\nStudents stack displayed successfully!\n");
}

void pop()
{
    if (top == -1)
    {
        printf("\nStack is empty!\n");
        return;
    }

    printf("\nDeleted Student:\n");
    printf("ID: %d\n", stack[top].id);
    printf("Name: %s\n", stack[top].name);
    printf("Marks: %.2f\n", stack[top].marks);

    top--;

    printf("\nStudent deleted successfully!\n");
}

void updateStudent()
{
    int id;
    int i;

    if (top == -1)
    {
        printf("\nStack is empty!\n");
        return;
    }

    id = readInt("Enter the ID of the student to update: ");

    if (id <= 0)
    {
        printf("Invalid ID! ID must be greater than 0.\n");
        return;
    }

    for (i = top; i >= 0; i--)
    {
        if (stack[i].id == id)
        {
            printf("\nStudent found!\n");
            printf("Current Name: %s\n", stack[i].name);
            printf("Current Marks: %.2f\n", stack[i].marks);

            printf("\nEnter new name: ");
            readName(stack[i].name, sizeof(stack[i].name));

            stack[i].marks = readMarks();

            printf("\nStudent updated successfully!\n");

            return;
        }
    }

    printf("\nStudent not found!\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n------ STUDENT STACK CRUD ------\n");

        printf("1. Create Student\n");
        printf("2. Read Stack\n");
        printf("3. Delete Student\n");
        printf("4. Update Student\n");
        printf("5. Exit\n");

        choice = readInt("Enter choice: ");

        switch (choice)
        {
            case 1:
                push();
                break;

            case 2:
                display();
                break;

            case 3:
                pop();
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
