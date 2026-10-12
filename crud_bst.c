#include <stdio.h>
#include <stdlib.h>
#define MAX_ATTEMPTS 3
struct tree
{
    int data;                 // Stores value
    struct tree *left;       // Points to left child
    struct tree *right;      // Points to right child
};
struct queue_node
{
    struct tree *tree_node;       // Stores address of tree node
    struct queue_node *next;      // Points to next queue node
};
// Queue using linked list
struct queue
{
    struct queue_node *front;     // Points to first queue node
    struct queue_node *rear;      // Points to last queue node
};
struct stack_node
{
    struct tree *tree_node;       // Stores address of tree node
    struct stack_node *next;      // Points to next stack node
};
// Stack using linked list
struct stack
{
    struct stack_node *top;       // Points to top stack node
};

struct tree *root = NULL;         // Root of BST
void init_queue(struct queue *q)
{
    //Queue is empty at first
    q->front = NULL;              
    q->rear = NULL;               
}

// Add a tree node to queue
void enqueue(struct queue *q, struct tree *node)
{
    struct queue_node *newNode;
    newNode = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->tree_node = node;   
    newNode->next = NULL;         // New node will be leave
    if (q->rear == NULL)
    {
        q->front = newNode;      
        q->rear = newNode;        
    }
    else
    {
        q->rear->next = newNode;  
        q->rear = newNode;       
    }
}
struct tree *dequeue(struct queue *q)
{
    struct queue_node *temp;
    struct tree *node;
    if (q->front == NULL)
        return NULL;
    temp = q->front;              
    node = temp->tree_node;       
    q->front = q->front->next;    
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);                   // Delete old queue node
    return node;                
}
int queue_is_empty(struct queue *q)
{
    if (q->front == NULL)
        return 1;
    return 0;
}

void init_stack(struct stack *s)
{
    s->top = NULL;                
}
void push(struct stack *s, struct tree *node)
{
    struct stack_node *newNode;
    newNode = (struct stack_node *)malloc(sizeof(struct stack_node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->tree_node = node;   
    newNode->next = s->top;       
    s->top = newNode;             
}
struct tree *pop(struct stack *s)
{
    struct stack_node *temp;
    struct tree *node;

    // If stack is empty
    if (s->top == NULL)
        return NULL;

    temp = s->top;              
    node = temp->tree_node;       // Get tree node
    s->top = s->top->next;        // Move top to next node
    free(temp);                   // Delete old stack node
    return node;                  // Return tree node
}
struct tree *peek(struct stack *s)
{
    if (s->top == NULL)
        return NULL;
    return s->top->tree_node;
}
int stack_is_empty(struct stack *s)
{
    if (s->top == NULL)
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
    newNode->data = value;        // Store value
    newNode->left = NULL;         // Initially no left child
    newNode->right = NULL;        // Initially no right child
    return newNode;
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
            temp = temp->right;   // Go right if value is larger
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
void insert(int value)
{
    struct tree *newNode;
    struct tree *temp;
    newNode = create_node(value);
    if (newNode == NULL)
        return;
    if (root == NULL)
    {
        root = newNode;
        printf("Node inserted successfully.\n");
        return;
    }
    temp = root;
    while (1)
    {
        // Smaller value goes left
        if (value < temp->data)
        {
            if (temp->left == NULL)
            {
                temp->left = newNode;
                printf("Node inserted successfully.\n");
                return;
            }
            temp = temp->left;
        }
        else
        {
            // Larger value goes right
            if (temp->right == NULL)
            {
                temp->right = newNode;
                printf("Node inserted successfully.\n");
                return;
            }
            temp = temp->right;
        }
    }
}
// Level-order traversal 
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
        // Add left child to queue
        if (temp->left != NULL)
            enqueue(&q, temp->left);
        // Add right child to queue
        if (temp->right != NULL)
            enqueue(&q, temp->right);
    }
    printf("\n");
}
// Preorder traversal using linked-list stack
void preorder_iterative()
{
    struct stack s;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    init_stack(&s);
    push(&s, root);               
    while (!stack_is_empty(&s))
    {
        struct tree *temp = pop(&s);
        printf("%d ", temp->data);
        // Push right first
        if (temp->right != NULL)
            push(&s, temp->right);
        // Push left second
        if (temp->left != NULL)
            push(&s, temp->left);
    }
    printf("\n");
}
// Inorder traversal using linked-list stack
void inorder_iterative()
{
    struct stack s;
    struct tree *temp = root;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    init_stack(&s);
    while (temp != NULL || !stack_is_empty(&s))
    {
        // Keep going left
        while (temp != NULL)
        {
            push(&s, temp);
            temp = temp->left;
        }
        temp = pop(&s);
        printf("%d ", temp->data);
        temp = temp->right;
    }
    printf("\n");
}
// Postorder traversal using linked-list stack
void postorder_iterative()
{
    struct stack s;
    struct tree *previous = NULL;
    struct tree *temp = root;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    init_stack(&s);
    while (temp != NULL || !stack_is_empty(&s))
    {
        while (temp != NULL)
        {
            push(&s, temp);
            temp = temp->left;
        }
        temp = peek(&s);
        // If right child is present and not visited
        if (temp->right != NULL && previous != temp->right)
        {
            temp = temp->right;
        }
        else
        {
            // Print node after left and right
            printf("%d ", temp->data);
            previous = temp;
            pop(&s);              // Remove from stack
            temp = NULL;
        }
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
                preorder_iterative();
                break;
            case 3:
                inorder_iterative();
                break;
            case 4:
                postorder_iterative();
                break;
            case 5:
                return;
        }
    }
}
void delete_node(int value)
{
    struct tree *parent = NULL; //parent of temp node
    struct tree *temp = root; //search for the pointer we have to delete
    struct tree *small_parent; //parent of small
    struct tree *small; //smallest node in right subtree
    struct tree *child;
    while (temp != NULL)
    {
        if (temp->data == value)
        {
            if (temp->left != NULL && temp->right != NULL)
            {
                small_parent = temp;
                small = temp->right;
                // Find smallest node on right side
                while (small->left != NULL)
                {
                    small_parent = small;
                    small = small->left;
                }
                // Copy smallest value
                temp->data = small->data;
                // Connect parent to small node's right child
                if (small_parent->left == small)
                    small_parent->left = small->right;
                else
                    small_parent->right = small->right;

                free(small);
                printf("Node deleted successfully.\n");
                return;
            }
            if (temp->left != NULL)
                child = temp->left;
            else
                child = temp->right;

            // If deleting root
            if (parent == NULL)
                root = child;
            // If node is left child
            else if (parent->left == temp)
                parent->left = child;
            // If node is right child
            else
                parent->right = child;

            free(temp);
            printf("Node deleted successfully.\n");
            return;
        }

        parent = temp;
        if (value < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    printf("Value not found.\n");
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
                delete_node(oldValue);   // Delete old value
                insert(newValue);        // Insert new value

                printf("Value updated successfully.\n");

                return;
            }
        }
    }

    printf("Invalid\n");
}

// Main function
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
        printf("--- Binary Search Tree ---\n");
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
                        delete_node(value);
                }

                break;

            case 5:

                printf("Program exited successfully.\n");

                return 0;
        }
    }

    return 0;
}