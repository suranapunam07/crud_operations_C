#include <stdio.h>

#define MAX 5

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

struct Student queue[MAX];

int front = -1;
int rear = -1;

void enqueue()
{
    if(rear == MAX - 1)
    {
        printf("Queue is FULL!");
        return;
    }
    struct Student s;
    
    printf("Enter Student ID:");
    scanf("%d",&s.id);

    printf("Enter student name:");
    scanf("%.[^n]",s.name);

    printf("Enter age: ");
    scanf("%d",&s.age);

    printf("Enter marks: ");
    scanf("%f",&s.marks);

    if(front == -1)
    {
        front = 0;
    }
    rear++;
    queue[rear] = s;

    printf("Student added successfully!");
}
void display()
{
    if(front == -1 || front > rear)
    {
        printf("\nQueue is empty!");
        return;
    }
    printf("\n===Student's Record===");

    for(int i = 0; i< rear; i++)
    {
        printf("\nID : %d", queue[i].id);
        printf("\nName : %s", queue[i].name);
        printf("\nAge : %d", queue[i].age);
        printf("\nMarks : %.2f\n", queue[i].marks);
    }
}
void update()
{
    int id;
    int found = 0;

    printf("Enter the id to be deleted:");
    scanf("%d",&id);

    for(int i = front; i <= rear; i++)
    {
        if(queue[i].id == id)
        {
            printf("Enter new Name: ");
            scanf("%.[^n]",queue[i].name);

            printf("Enter new age: ");
            scanf("%d",&queue[i].age);

            printf("Enter new marks: ");
            scanf("%f",&queue[i].marks);

            printf("Student updated successfully!!");
            found = 1;
            break;
        }
        if(!found)
        {
            printf("Student not found!!");
        }
    }
}

void dequeue()
{
    if(front == -1 || front > rear)
    {
        printf("\nQueue is empty!");
        return;
    }
    printf("Deleted Student: %s\n",queue[front].name);

    front++;

    if(front > rear)
    {
        front = -1;
        rear = -1;
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n===== QUEUE CRUD =====");
        printf("\n1. Create / Enqueue");
        printf("\n2. Read / Display");
        printf("\n3. Update");
        printf("\n4. Delete / Dequeue");
        printf("\n5. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

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
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
