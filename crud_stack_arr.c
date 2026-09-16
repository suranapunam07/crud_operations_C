#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 5

struct Student {
    int id;
    char name[50];
    float marks;
};

struct Student stack[MAX];
int top = -1;

int readInt(char message[]) {
    char input[100], extra;
    int value;
    while(1) {
        printf("%s", message);
        if(fgets(input,sizeof(input),stdin) == NULL) exit(0);
        if(sscanf(input,"%d %c",&value,&extra) == 1) return value;
        printf("Invalid\n");
    }
}

float readFloat(char message[]) {
    char input[100], extra;
    float value;
    while(1) {
        printf("%s", message);
        if(fgets(input,sizeof(input),stdin) == NULL) exit(0);
        if(sscanf(input,"%f %c",&value,&extra) == 1) return value;
        printf("Invalid\n");
    }
}

int validName(char name[]) {
    int i;
    if(strlen(name) == 0) return 0;
    for(i=0; name[i]!='\0'; i++) {
        if(!isalpha((unsigned char)name[i]) && name[i] != ' ') return 0;
    }
    return 1;
}

void readName(char name[], int size) {
    while(1) {
        if(fgets(name,size,stdin) == NULL) exit(0);
        name[strcspn(name,"\n")] = '\0';
        if(validName(name)) return;
        printf("Invalid\n");
    }
}

int idExists(int searchID) {
    for(int i=0; i<=top; i++) {
        if(stack[i].id == searchID) return 1;
    }
    return 0;
}

int readID() {
    int id;
    while(1) {
        id = readInt("Enter Student ID: ");
        if(id <= 0) {
            printf("Invalid\n");
        } else if(idExists(id)) {
            printf("Invalid\n");
        } else {
            return id;
        }
    }
}

float readMarks() {
    float marks;
    while(1) {
        marks = readFloat("Enter Student Marks: ");
        if(marks < 0 || marks > 100) {
            printf("Invalid\n");
        } else {
            return marks;
        }
    }
}

void push() {
    struct Student s;
    if(top == MAX-1) {
        printf("Invalid\n");
        return;
    }
    s.id = readID();
    printf("Enter Student Name: ");
    readName(s.name,sizeof(s.name));
    s.marks = readMarks();
    stack[++top] = s;
    printf("Added\n");
}

void display() {
    if(top == -1) {
        printf("Invalid\n");
        return;
    }
    for(int i=top; i>=0; i--) {
        printf("ID: %d | Name: %s | Marks: %.2f\n", stack[i].id, stack[i].name, stack[i].marks);
    }
}

void pop() {
    if(top == -1) {
        printf("Invalid\n");
        return;
    }
    printf("Deleted: ID: %d | Name: %s | Marks: %.2f\n", stack[top].id, stack[top].name, stack[top].marks);
    top--;
}

void updateStudent() {
    if(top == -1) {
        printf("Invalid\n");
        return;
    }
    int id = readInt("Enter ID to update: ");
    if(id <= 0) {
        printf("Invalid\n");
        return;
    }
    for(int i=top; i>=0; i--) {
        if(stack[i].id == id) {
            printf("Enter new name: ");
            readName(stack[i].name,sizeof(stack[i].name));
            stack[i].marks = readMarks();
            printf("Updated\n");
            return;
        }
    }
    printf("Invalid\n");
}

int main() {
    int choice;
    while(1) {
        printf("\n1. Create\n2. Read\n3. Delete\n4. Update\n5. Exit\n");
        choice = readInt("Enter choice: ");
        switch(choice) {
            case 1: push(); break;
            case 2: display(); break;
            case 3: pop(); break;
            case 4: updateStudent(); break;
            case 5: return 0;
            default: printf("Invalid\n");
        }
    }
}
