
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Student {
    unsigned long long int id;
    char name[50];
    float marks;
    struct Student *next;
};

struct Student *front = NULL;
struct Student *rear = NULL;

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
    struct Student *temp = front;

    while (temp != NULL) {
        if (temp->id == searchID)
            return 1;

        temp = temp->next;
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

float readMarks() {
    float marks;

    while (1) {
        marks = readFloat("Enter Student Marks: ");

        if (marks < 0 || marks > 100) {
            printf("Invalid\n");
        }
        else {
            return marks;
        }
    }
}

void enqueue() {
    struct Student *newNode =
        (struct Student *)malloc(sizeof(struct Student));

    if (newNode == NULL) {
        printf("Invalid\n");
        return;
    }

    newNode->id = readID();

    printf("Enter Student Name: ");
    readName(newNode->name, sizeof(newNode->name));

    newNode->marks = readMarks();
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }

    printf("Added!\n");
}

void readQueue() {
    if (front == NULL) {
        printf("Invalid\n");
        return;
    }

    struct Student *temp = front;

    printf("\nID\tName\tMarks\n");
    printf("-------------------------\n");

    while (temp != NULL) {
        printf("%llu\t%s\t%.2f\n",
               temp->id,
               temp->name,
               temp->marks);

        temp = temp->next;
    }
}

void dequeue() {
    if (front == NULL) {
        printf("Invalid\n");
        return;
    }

    struct Student *temp = front;

    printf("Deleted: %llu %s %.2f\n",
           temp->id,
           temp->name,
           temp->marks);

    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);

    printf("Deleted!\n");
}

void updateStudent() {
    if (front == NULL) {
        printf("Invalid\n");
        return;
    }

    unsigned long long int id =
        readSearchID("Enter ID to Update: ");

    struct Student *temp = front;
    int found = 0;

    while (temp != NULL) {
        if (temp->id == id) {
            printf("Enter new name: ");
            readName(temp->name, sizeof(temp->name));

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

int main() {
    int choice;

    while (1) {
        printf("\nSTUDENT QUEUE CRUD\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Delete\n");
        printf("4. Update\n");
        printf("5. Exit\n");

        choice = readInt("Enter choice: ");

        switch (choice) {
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
}
