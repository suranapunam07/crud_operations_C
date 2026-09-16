#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#define MAX_ATTEMPTS 3

struct Student {
    unsigned int id;
    char name[50];
    float marks;
    struct Student *left;
    struct Student *right;
};

int isValidName(char name[]) {
    int hasLetter = 0;

    if (strlen(name) == 0)
        return 0;

    for (int i = 0; name[i] != '\0'; i++) {
        if (isalpha((unsigned char)name[i])) {
            hasLetter = 1;
        } else if (name[i] != ' ') {
            return 0;
        }
    }

    return hasLetter;
}

struct Student *search(struct Student *root, unsigned int id) {
    struct Student *queue[100];
    int front = 0, rear = 0;
    struct Student *temp;

    if (root == NULL)
        return NULL;

    queue[rear++] = root;

    while (front < rear) {
        temp = queue[front++];

        if (temp->id == id)
            return temp;

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }

    return NULL;
}

unsigned int getValidId(struct Student *root) {
    char input[100], extra;
    unsigned long long value;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter Student ID: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (input[0] == '-') {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (sscanf(input, "%llu %c", &value, &extra) != 1) {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (value == 0 || value > UINT_MAX) {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (root != NULL && search(root, (unsigned int)value) != NULL) {
            printf("Invalid (duplicate ID)\n");
            attempts++;
            continue;
        }

        return (unsigned int)value;
    }

    printf("Invalid\n");
    return (unsigned int)-1;
}

int getExistingId(struct Student *root, unsigned int *id) {
    char input[100], extra;
    unsigned long long value;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter Student ID: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (input[0] == '-') {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (sscanf(input, "%llu %c", &value, &extra) != 1) {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (value == 0 || value > UINT_MAX) {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        *id = (unsigned int)value;

        if (search(root, *id) == NULL) {
            printf("Invalid (ID not found)\n");
            attempts++;
            continue;
        }

        return 1;
    }

    printf("Invalid\n");
    return 0;
}

int getValidName(char name[]) {
    int attempts = 0;
    int length;
    int ch;

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter Student Name: ");

        if (fgets(name, 50, stdin) == NULL) {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        length = strlen(name);

        if (length > 0 && name[length - 1] == '\n') {
            name[length - 1] = '\0';
        } else {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (isValidName(name))
            return 1;

        printf("Invalid\n");
        attempts++;
    }

    printf("Invalid\n");
    return 0;
}

float getValidMarks() {
    char input[100], extra;
    float marks;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter Student Marks: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Invalid\n");
            attempts++;
            continue;
        }

        if (sscanf(input, "%f %c", &marks, &extra) == 1) {
            if (isfinite(marks) && marks >= 0 && marks <= 100)
                return marks;
        }

        printf("Invalid\n");
        attempts++;
    }

    printf("Invalid\n");
    return -1;
}

struct Student *createNode(unsigned int id, char name[], float marks) {
    struct Student *newNode;

    newNode = (struct Student *)malloc(sizeof(struct Student));

    if (newNode == NULL)
        return NULL;

    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->marks = marks;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Student *insert(struct Student *root, unsigned int id, char name[], float marks) {
    struct Student *queue[100];
    int front = 0, rear = 0;
    struct Student *temp;
    struct Student *newNode;

    newNode = createNode(id, name, marks);

    if (newNode == NULL)
        return NULL;

    if (root == NULL)
        return newNode;

    queue[rear++] = root;

    while (front < rear) {
        temp = queue[front++];

        if (temp->left == NULL) {
            temp->left = newNode;
            return root;
        } else {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = newNode;
            return root;
        } else {
            queue[rear++] = temp->right;
        }
    }

    free(newNode);
    return root;
}

void inorder(struct Student *root) {
    if (root != NULL) {
        inorder(root->left);

        printf("ID: %u | Name: %s | Marks: %.2f\n",
               root->id,
               root->name,
               root->marks);

        inorder(root->right);
    }
}

void createStudent(struct Student **root) {
    unsigned int id;
    char name[50];
    float marks;
    struct Student *newRoot;

    id = getValidId(*root);

    if (id == (unsigned int)-1)
        return;

    if (!getValidName(name))
        return;

    marks = getValidMarks();

    if (marks == -1)
        return;

    newRoot = insert(*root, id, name, marks);

    if (newRoot == NULL) {
        printf("Invalid\n");
        return;
    }

    *root = newRoot;

    printf("Added!\n");
}

void readStudents(struct Student *root) {
    if (root == NULL) {
        printf("Invalid\n");
        return;
    }

    inorder(root);
}

void updateStudent(struct Student *root) {
    unsigned int id;
    struct Student *temp;
    char name[50];
    float marks;

    if (root == NULL) {
        printf("Invalid\n");
        return;
    }

    if (!getExistingId(root, &id))
        return;

    temp = search(root, id);

    if (!getValidName(name))
        return;

    marks = getValidMarks();

    if (marks == -1)
        return;

    strcpy(temp->name, name);
    temp->marks = marks;

    printf("Updated!\n");
}

void deleteDeepest(struct Student *root, struct Student *deepest) {
    struct Student *queue[100];
    int front = 0, rear = 0;
    struct Student *temp;

    if (root == NULL)
        return;

    queue[rear++] = root;

    while (front < rear) {
        temp = queue[front++];

        if (temp->left != NULL) {
            if (temp->left == deepest) {
                free(temp->left);
                temp->left = NULL;
                return;
            }

            queue[rear++] = temp->left;
        }

        if (temp->right != NULL) {
            if (temp->right == deepest) {
                free(temp->right);
                temp->right = NULL;
                return;
            }

            queue[rear++] = temp->right;
        }
    }
}

struct Student *getDeepestNode(struct Student *root) {
    struct Student *queue[100];
    int front = 0, rear = 0;
    struct Student *temp = NULL;

    if (root == NULL)
        return NULL;

    queue[rear++] = root;

    while (front < rear) {
        temp = queue[front++];

        if (temp->left != NULL)
            queue[rear++] = temp->left;

        if (temp->right != NULL)
            queue[rear++] = temp->right;
    }

    return temp;
}

void deleteStudentOperation(struct Student **root) {
    unsigned int id;
    struct Student *target;
    struct Student *deepest;

    if (*root == NULL) {
        printf("Invalid\n");
        return;
    }

    if (!getExistingId(*root, &id))
        return;

    target = search(*root, id);
    deepest = getDeepestNode(*root);

    if (target == deepest) {
        free(deepest);
        *root = NULL;
        printf("Deleted!\n");
        return;
    }

    target->id = deepest->id;
    strcpy(target->name, deepest->name);
    target->marks = deepest->marks;

    deleteDeepest(*root, deepest);

    printf("Deleted!\n");
}

void freeTree(struct Student *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Student *root = NULL;
    int choice, attempts;
    char input[100], extra;

    while (1) {
        printf("\n1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        attempts = 0;

        while (attempts < MAX_ATTEMPTS) {
            printf("Enter choice: ");

            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("Invalid\n");
                attempts++;
                continue;
            }

            if (sscanf(input, "%d %c", &choice, &extra) == 1) {
                if (choice >= 1 && choice <= 5)
                    break;
            }

            printf("Invalid\n");
            attempts++;
        }

        if (attempts == MAX_ATTEMPTS) {
            printf("Invalid\n");
            continue;
        }

        switch (choice) {
            case 1:
                createStudent(&root);
                break;

            case 2:
                readStudents(root);
                break;

            case 3:
                updateStudent(root);
                break;

            case 4:
                deleteStudentOperation(&root);
                break;

            case 5:
                freeTree(root);
                return 0;
        }
    }
}