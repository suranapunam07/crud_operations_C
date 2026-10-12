// -1  → right side slightly taller 
//  0  → both sides same height     
// +1  → left side slightly taller  
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define MAX_ATTEMPTS 3

struct tree
{
    int data;
    int height;
    struct tree *left;
    struct tree *right;
};
struct queue
{
    struct tree *items[MAX_SIZE];
    int front;
    int rear;
};
struct tree *root = NULL;
void init_queue(struct queue *q)
{
    q->front = 0;
    q->rear = 0;
}
void enqueue(struct queue *q, struct tree *node)
{
    if (q->rear < MAX_SIZE)
    {
        q->items[q->rear] = node;
        q->rear++;
    }
}
struct tree *dequeue(struct queue *q)
{
    struct tree *node;
    if (q->front >= q->rear)
        return NULL;
    node = q->items[q->front];
    q->front++;
    return node;
}
int queue_is_empty(struct queue *q)
{
    if (q->front >= q->rear)
        return 1;
    return 0;
}

struct tree *create_node(int value)
{
    struct tree *newNode;
    newNode = (struct tree *)malloc(sizeof(struct tree));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Returns the height of the given node 
int height_of(struct tree *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int max_value(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

// Balance factor tells whether the node is balanced
int balance_of(struct tree *node)
{
    if (node == NULL)
        return 0;
    return height_of(node->left) - height_of(node->right);
}

// Update height after insertion, deletion or rotation 
void update_height(struct tree *node)
{
    if (node != NULL)
    {
        node->height = 1 + max_value( height_of(node->left),height_of(node->right));
    }
}

//Right rotation is used mainly for LL imbalance
struct tree *right_rotate(struct tree *y)
{
    struct tree *x;
    struct tree *temp;
    x = y->left;
    temp = x->right;
    x->right = y;
    y->left = temp;
    update_height(y);
    update_height(x);
    return x;
}

/* Left rotation is used mainly for RR imbalance */
struct tree *left_rotate(struct tree *x)
{
    struct tree *y;
    struct tree *temp;
    y = x->right;
    temp = y->left;
    y->left = x;
    x->right = temp;
    update_height(x);
    update_height(y);
    return y;
}

int isValueExists(int value)
{
    struct tree *temp = root;
    while (temp != NULL)
    {
        if (value == temp->data)
            return 1;
        if (value < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return 0;
}

int getValidValue(int *status)
{
    int value;
    int attempts = 0;
    char ch;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter value: ");
        if (scanf("%d", &value) != 1)
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
            else if (isValueExists(value))
            {
                printf("Value already exists.\n");
                attempts++;
            }
            else
            {
                *status = 1;
                return value;
            }
        }
    }

    printf("Invalid\n");

    *status = 0;

    return 0;
}

int getSearchValue(int *status)
{
    int value;
    int attempts = 0;
    char ch;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter value: ");

        if (scanf("%d", &value) != 1)
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
            else if (!isValueExists(value))
            {
                printf("Value not found.\n");
                attempts++;
            }
            else
            {
                *status = 1;
                return value;
            }
        }
    }

    printf("Invalid\n");

    *status = 0;

    return 0;
}

struct tree *insert_node(struct tree *node, int value)
{
    int balance;

    if (node == NULL)
        return create_node(value);

    if (value < node->data)
    {
        node->left = insert_node(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insert_node(node->right, value);
    }
    else
    {
        return node;
    }

    // Update height after inserting the new node 
    update_height(node);
    balance = balance_of(node);
    // LL case
    if (balance > 1 && value < node->left->data)
    {
        return right_rotate(node);
    }
    // RR case 
    if (balance < -1 && value > node->right->data)
    {
        return left_rotate(node);
    }
    // LR case 
    if (balance > 1 && value > node->left->data)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    //RL case 
    if (balance < -1 && value < node->right->data)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void insert(int value)
{
    root = insert_node(root, value);

    printf("Node inserted successfully.\n");
}

struct tree *find_min(struct tree *node)
{
    struct tree *temp = node;

    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}

struct tree *delete_node(struct tree *node, int value)
{
    int balance;
    struct tree *temp;

    if (node == NULL)
        return NULL;

    if (value < node->data)
    {
        node->left = delete_node(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = delete_node(node->right, value);
    }
    else
    {
        /* Case 1: node has no child */
        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            return NULL;
        }

        /* Case 2: node has only right child */
        if (node->left == NULL)
        {
            temp = node->right;
            free(node);
            return temp;
        }

        /* Case 3: node has only left child */
        if (node->right == NULL)
        {
            temp = node->left;
            free(node);
            return temp;
        }

        /* Case 4: node has two children */
        temp = find_min(node->right);

        node->data = temp->data;

        node->right = delete_node(node->right, temp->data);
    }

    /* Recalculate height after deletion */
    update_height(node);

    balance = balance_of(node);

    /* LL case */
    if (balance > 1 && balance_of(node->left) >= 0)
    {
        return right_rotate(node);
    }

    /* LR case */
    if (balance > 1 && balance_of(node->left) < 0)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    /* RR case */
    if (balance < -1 && balance_of(node->right) <= 0)
    {
        return left_rotate(node);
    }

    /* RL case */
    if (balance < -1 && balance_of(node->right) > 0)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void delete_value(int value)
{
    root = delete_node(root, value);

    printf("Node deleted successfully.\n");
}

void preorder(struct tree *node)
{
    if (node == NULL)
        return;

    printf("%d ", node->data);

    preorder(node->left);
    preorder(node->right);
}

void inorder(struct tree *node)
{
    if (node == NULL)
        return;

    inorder(node->left);

    printf("%d ", node->data);

    inorder(node->right);
}

void postorder(struct tree *node)
{
    if (node == NULL)
        return;

    postorder(node->left);
    postorder(node->right);

    printf("%d ", node->data);
}

void normal_order()
{
    struct queue q;

    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    init_queue(&q);
    enqueue(&q, root);

    while (!queue_is_empty(&q))
    {
        struct tree *temp = dequeue(&q);

        printf("%d ", temp->data);

        if (temp->left != NULL)
            enqueue(&q, temp->left);

        if (temp->right != NULL)
            enqueue(&q, temp->right);
    }

    printf("\n");
}

void read_tree()
{
    int choice;
    int attempts;
    char ch;

    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    while (1)
    {
        printf("\n");
        printf("--- Read Tree ---\n");
        printf("1. Normal Order\n");
        printf("2. Preorder\n");
        printf("3. Inorder\n");
        printf("4. Postorder\n");
        printf("5. Back\n");

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
            return;
        }

        switch (choice)
        {
            case 1:
                normal_order();
                break;

            case 2:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;

            case 3:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;

            case 5:
                return;
        }
    }
}

void update_node()
{
    int oldValue;
    int newValue;
    int status;
    int attempts;
    char ch;

    oldValue = getSearchValue(&status);

    if (status == 0)
        return;

    attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter new value: ");

        if (scanf("%d", &newValue) != 1)
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
            else if (newValue == oldValue)
            {
                printf("Invalid\n");

                attempts++;
            }
            else if (isValueExists(newValue))
            {
                printf("New value already exists.\n");

                attempts++;
            }
            else
            {
                root = delete_node(root, oldValue);
                root = insert_node(root, newValue);

                printf("Value updated successfully.\n");

                return;
            }
        }
    }

    printf("Invalid\n");
}

int main()
{
    int choice;
    int value;
    int status;
    int attempts;
    char ch;

    while (1)
    {
        printf("\n");
        printf("--- AVL Tree ---\n");
        printf("1. Insert\n");
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
                value = getValidValue(&status);

                if (status == 1)
                    insert(value);

                break;

            case 2:
                read_tree();
                break;

            case 3:
                if (root == NULL)
                {
                    printf("Tree is empty.\n");
                }
                else
                {
                    update_node();
                }

                break;

            case 4:
                if (root == NULL)
                {
                    printf("Tree is empty.\n");
                }
                else
                {
                    value = getSearchValue(&status);

                    if (status == 1)
                        delete_value(value);
                }

                break;

            case 5:
                printf("Program exited successfully.\n");
                return 0;
        }
    }

    return 0;
}