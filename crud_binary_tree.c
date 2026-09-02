#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int id;
    char name[50];
    float marks;
    struct Student *left;
    struct Student *right;
};

struct Student *createNode(int id, char name[], float marks)
{
    struct Student *newNode;

    newNode = (struct Student *)malloc(sizeof(struct Student));

    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->marks = marks;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Student *insert(struct Student *root, int id, char name[], float marks)
{
    struct Student *queue[100];
    int front = 0;
    int rear = 0;
    struct Student *temp;

    if (root == NULL)
    {
        return createNode(id, name, marks);
    }

    queue[rear++] = root;

    while (front < rear)
    {
        temp = queue[front++];

        if (temp->left == NULL)
        {
            temp->left = createNode(id, name, marks);
            return root;
        }
        else
        {
            queue[rear++] = temp->left;
        }

        if (temp->right == NULL)
        {
            temp->right = createNode(id, name, marks);
            return root;
        }
        else
        {
            queue[rear++] = temp->right;
        }
    }

    return root;
}

struct Student *search(struct Student *root, int id)
{
    struct Student *queue[100];
    int front = 0;
    int rear = 0;
    struct Student *temp;

    if (root == NULL)
    {
        return NULL;
    }

    queue[rear++] = root;

    while (front < rear)
    {
        temp = queue[front++];

        if (temp->id == id)
        {
            return temp;
        }

        if (temp->left != NULL)
        {
            queue[rear++] = temp->left;
        }

        if (temp->right != NULL)
        {
            queue[rear++] = temp->right;
        }
    }

    return NULL;
}

void inorder(struct Student *root)
{
    if (root != NULL)
    {
        inorder(root->left);

        printf("ID: %d | Name: %s | Marks: %.2f\n",
               root->id,
               root->name,
               root->marks);

        inorder(root->right);
    }
}

void preorder(struct Student *root)
{
    if (root != NULL)
    {
        printf("ID: %d | Name: %s | Marks: %.2f\n",
               root->id,
               root->name,
               root->marks);

        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Student *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);

        printf("ID: %d | Name: %s | Marks: %.2f\n",
               root->id,
               root->name,
               root->marks);
    }
}

struct Student *getDeepestNode(struct Student *root)
{
    struct Student *queue[100];
    int front = 0;
    int rear = 0;
    struct Student *temp = NULL;

    queue[rear++] = root;

    while (front < rear)
    {
        temp = queue[front++];

        if (temp->left != NULL)
        {
            queue[rear++] = temp->left;
        }

        if (temp->right != NULL)
        {
            queue[rear++] = temp->right;
        }
    }

    return temp;
}

void deleteDeepest(struct Student *root, struct Student *deepest)
{
    struct Student *queue[100];
    int front = 0;
    int rear = 0;
    struct Student *temp;

    queue[rear++] = root;

    while (front < rear)
    {
        temp = queue[front++];

        if (temp->left != NULL)
        {
            if (temp->left == deepest)
            {
                temp->left = NULL;
                free(deepest);
                return;
            }

            queue[rear++] = temp->left;
        }

        if (temp->right != NULL)
        {
            if (temp->right == deepest)
            {
                temp->right = NULL;
                free(deepest);
                return;
            }

            queue[rear++] = temp->right;
        }
    }
}

struct Student *deleteStudent(struct Student *root, int id)
{
    struct Student *queue[100];
    int front = 0;
    int rear = 0;
    struct Student *temp;
    struct Student *target = NULL;
    struct Student *deepest;

    if (root == NULL)
    {
        return NULL;
    }

    if (root->left == NULL && root->right == NULL)
    {
        if (root->id == id)
        {
            free(root);
            return NULL;
        }

        return root;
    }

    queue[rear++] = root;

    while (front < rear)
    {
        temp = queue[front++];

        if (temp->id == id)
        {
            target = temp;
        }

        if (temp->left != NULL)
        {
            queue[rear++] = temp->left;
        }

        if (temp->right != NULL)
        {
            queue[rear++] = temp->right;
        }
    }

    if (target == NULL)
    {
        return root;
    }

    deepest = getDeepestNode(root);

    target->id = deepest->id;
    strcpy(target->name, deepest->name);
    target->marks = deepest->marks;

    deleteDeepest(root, deepest);

    return root;
}

void createStudent(struct Student **root)
{
    int id;
    char name[50];
    float marks;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", name);

    printf("Enter Student Marks: ");
    scanf("%f", &marks);

    *root = insert(*root, id, name, marks);

    printf("\nStudent added successfully!\n");
}

void readStudents(struct Student *root)
{
    if (root == NULL)
    {
        printf("\nTree is empty!\n");
        return;
    }

    printf("\n========== INORDER ==========\n");
    inorder(root);
}

void updateStudent(struct Student *root)
{
    int id;
    struct Student *temp;

    if (root == NULL)
    {
        printf("\nTree is empty!\n");
        return;
    }

    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    temp = search(root, id);

    if (temp == NULL)
    {
        printf("\nStudent not found!\n");
        return;
    }

    printf("\nStudent found!\n");
    printf("Current Name: %s\n", temp->name);
    printf("Current Marks: %.2f\n", temp->marks);

    printf("\nEnter new name: ");
    scanf(" %[^\n]", temp->name);

    printf("Enter new marks: ");
    scanf("%f", &temp->marks);

    printf("\nStudent updated successfully!\n");
}

void deleteStudentOperation(struct Student **root)
{
    int id;

    if (*root == NULL)
    {
        printf("\nTree is empty!\n");
        return;
    }

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    if (search(*root, id) == NULL)
    {
        printf("\nStudent not found!\n");
        return;
    }

    *root = deleteStudent(*root, id);

    printf("\nStudent deleted successfully!\n");
}

int main()
{
    struct Student *root = NULL;
    int choice;

    while (1)
    {
        printf("\n\n========== STUDENT BINARY TREE CRUD ==========\n");

        printf("1. Create Student\n");
        printf("2. Read Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
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
                printf("\nProgram exited.\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}