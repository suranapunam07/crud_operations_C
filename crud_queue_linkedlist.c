#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float marks;
    struct Student* next;
};

struct Student* front = NULL;
struct Student* rear = NULL;

void enqueue() {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    if (newNode == NULL) {
        printf("Unable to allocate memory!\n");
        return;
    }

    printf("Enter student ID: ");
    scanf("%d", &newNode->id);

    printf("Enter student Name: ");
    scanf(" %[^\n]", newNode->name); 

    printf("Enter student Marks: ");
    scanf("%f", &newNode->marks);

    newNode->next = NULL;

    if (rear == NULL) 
    {
        front = rear = newNode;
    } else 
    {
        rear->next = newNode;
        rear = newNode;
    }

    printf("\nStudent added successfully!\n");
}


void readQueue() 
{
    if (front == NULL) 
    {
        printf("Queue is empty!\n");
        return;
    }
    struct Student* temp = front;
    printf("\nStudent Queue\n");
    while (temp != NULL) 
    {
        printf("ID: %d | Name: %s | Marks: %.2f\n", temp->id, temp->name, temp->marks);
        temp = temp->next;
    }
    printf("\nStudents queue displayed successfully!!");
}

void dequeue()
{
    struct Student* temp;

    if (front == NULL)
    {
        printf("Queue is empty!\n");
        return;
    }

    temp = front;

    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);

    printf("Student deleted successfully!!\n");
}
  
void updateStudent()
{
    if(front == NULL)
    {
        printf("\n Queue is empty!");
        return;
    }
    int id;
    printf("Enter the id of the student to update: ");
    scanf("%d",&id);

    struct Student* temp = front;
    while(temp != NULL && temp->id != id)
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        printf("Student not found!!");
        return;
    }
    printf("Enter the new marks of the student: ");
    scanf("%f",&temp->marks);

    printf("\nMarks Updated Successfully!!");
}

int main() 
{
    int choice;
    while (1) 
    {
        printf("\n1. Create Student");
        printf("\n2. Read Queue");
        printf("\n3. Delete Student");
        printf("\n4. Update Student");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

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
                printf("Program exited.\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
