#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX 5

struct Student {
    unsigned long long int id;
    char name[50];
    int age;
    float marks;
};

struct Student queue[MAX];
int front = -1;
int rear = -1;

int readInt(char message[]) {
    char input[100], extra;
    int value;

    while (1) {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        if (sscanf(input, "%d %c", &value, &extra) == 1)
            return value;

        printf("Invalid\n");
    }
}

float readFloat(char message[]) {
    char input[100], extra;
    float value;

    while (1) {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        if (sscanf(input, "%f %c", &value, &extra) == 1)
            return value;

        printf("Invalid\n");
    }
}

int validName(char name[]) {
    if (strlen(name) == 0)
        return 0;

    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
            return 0;
    }

    return 1;
}

void readName(char name[], int size) {
    while (1) {
        if (fgets(name, size, stdin) == NULL)
            exit(0);

        name[strcspn(name, "\n")] = '\0';

        if (validName(name))
            return;

        printf("Invalid\n");
    }
}

int idExists(unsigned long long int searchID) {
    if (front == -1)
        return 0;

    for (int i = front; i <= rear; i++) {
        if (queue[i].id == searchID)
            return 1;
    }

    return 0;
}

unsigned long long int readID() {
    char input[100], extra;
    unsigned long long int id;

    while (1) {
        printf("Enter Student ID: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        if (input[0] == '-') {
            printf("Invalid\n");
            continue;
        }

        if (sscanf(input, "%llu %c", &id, &extra) != 1) {
            printf("Invalid\n");
            continue;
        }

        if (id == 0 || idExists(id)) {
            printf("Invalid\n");
            continue;
        }

        return id;
    }
}

unsigned long long int readSearchID(char message[]) {
    char input[100], extra;
    unsigned long long int id;

    while (1) {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        if (input[0] == '-') {
            printf("Invalid\n");
            continue;
        }

        if (sscanf(input, "%llu %c", &id, &extra) != 1) {
            printf("Invalid\n");
            continue;
        }

        if (id == 0) {
            printf("Invalid\n");
            continue;
        }

        return id;
    }
}

int readAge() {
    int age;

    while (1) {
        age = readInt("Enter Age: ");

        if (age < 5 || age > 100) {
            printf("Invalid\n");
        }
        else {
            return age;
        }
    }
}

float readMarks() {
    float marks;

    while (1) {
        marks = readFloat("Enter Marks: ");

        if (marks < 0 || marks > 100) {
            printf("Invalid\n");
        }
        else {
            return marks;
        }
    }
}

void enqueue() {
    if (rear == MAX - 1) {
        printf("Invalid\n");
        return;
    }

    struct Student s;

    s.id = readID();

    printf("Enter Student Name: ");
    readName(s.name, sizeof(s.name));

    s.age = readAge();
    s.marks = readMarks();

    if (front == -1)
        front = 0;

    queue[++rear] = s;

    printf("Added!\n");
}

void display() {
    if (front == -1 || front > rear) {
        printf("Invalid\n");
        return;
    }

    printf("\nID\tName\tAge\tMarks\n");
    printf("-----------------------------\n");

    for (int i = front; i <= rear; i++) {
        printf("%llu\t%s\t%d\t%.2f\n",
               queue[i].id,
               queue[i].name,
               queue[i].age,
               queue[i].marks);
    }
}

void update() {
    if (front == -1 || front > rear) {
        printf("Invalid\n");
        return;
    }

    unsigned long long int search;
    search = readSearchID("Enter ID to Update: ");

    int found = 0;

    for (int i = front; i <= rear; i++) {
        if (queue[i].id == search) {
            printf("Enter new name: ");
            readName(queue[i].name, sizeof(queue[i].name));

            queue[i].age = readAge();
            queue[i].marks = readMarks();

            found = 1;

            printf("Updated!\n");
            break;
        }
    }

    if (!found)
        printf("Invalid\n");
}

void dequeue() {
    if (front == -1 || front > rear) {
        printf("Invalid\n");
        return;
    }

    printf("Deleted: %llu %s %d %.2f\n",
           queue[front].id,
           queue[front].name,
           queue[front].age,
           queue[front].marks);

    front++;

    if (front > rear) {
        front = -1;
        rear = -1;
    }

    printf("Deleted!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nSTUDENT QUEUE CRUD\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        choice = readInt("Enter choice: ");

        switch (choice) {
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
                printf("Invalid\n");
        }
    }
}
