#include <stdio.h>
#include <stdlib.h>
#define MAX_ATTEMPTS 3

//structure for one tree node.
struct tree
{
    int data;
    struct tree *left;//left child pointer
    struct tree *right;//right child pointer
};
//separate structure for the queue.
struct queue
{
    struct tree *items[100];
    int front;  //Keeps track of the next node to remove.
    int rear;   //Keeps track of where the next node will be inserted.
};

//separate structure for the stack.
struct stack
{
    struct tree *items[100];
    int top;  //Keeps track of the top of the stack.
};

struct tree *root = NULL; //address of root node of the tree.

void init_queue(struct queue *q)  //initiallize queue
{
    q->front = 0;
    q->rear = 0;
}

void enqueue(struct queue *q, struct tree *node)
{
    if (q->rear < 100)
    {
        q->items[q->rear] = node;
        q->rear++;
    }
}

struct tree *dequeue(struct queue *q)
{
    struct tree *node;
    if (q->front >= q->rear) //If front has reached rear, there is nothing to remove.
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

void init_stack(struct stack *s)
{
    s->top = -1;
}

void push(struct stack *s, struct tree *node)  //push() adds a node to the top of the stack.
{
    if (s->top < 99)
    {
        s->top++;
        s->items[s->top] = node;
    }
}

struct tree *pop(struct stack *s)  //pop() removes and returns the top node from the stack
{
    if (s->top == -1)
        return NULL;
    return s->items[s->top--];
}

struct tree *peek(struct stack *s) //for postorder trsversal to check the child of the node.
{
    if (s->top == -1)
        return NULL;
    return s->items[s->top];
}

int stack_is_empty(struct stack *s)  //to know whether there is anything left.
{
    if (s->top == -1)
        return 1;
    return 0;
}

int isValueExists(int value)
{
    struct queue q;
    if (root == NULL)
        return 0;
    init_queue(&q);
    enqueue(&q, root);
    while (!queue_is_empty(&q))
    {
        struct tree *temp = dequeue(&q);
        if (temp->data == value)
            return 1;
        if (temp->left != NULL)
            enqueue(&q, temp->left);
        if (temp->right != NULL)
            enqueue(&q, temp->right);
    }
    return 0;
}

int getValidValue(int *valid)
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
                printf("Invalid\n");
                attempts++;
            }
            else
            {
                *valid = 1;
                return value;
            }
        }
    }
    printf("Invalid\n");
    *valid = 0;
    return 0;
}

int getSearchValue(int *valid)
{
    int value;
    int attempts = 0;
    char ch;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter value to search: ");

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
            else
            {
                *valid = 1;
                return value;
            }
        }
    }

    printf("Invalid\n");
    *valid = 0;
    return 0;
}



//create

struct tree *create_node()
{
    int value;
    int valid;
    struct tree *newNode;

    value = getValidValue(&valid);

    if (valid == 0)
        return root;

    newNode = (struct tree *)malloc(sizeof(struct tree));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return root;
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if (root == NULL)
    {
        root = newNode;
        printf("Node inserted successfully.\n");
        return root;
    }

    struct queue q;
    init_queue(&q);

    enqueue(&q, root);

    while (!queue_is_empty(&q))
    {
        struct tree *temp = dequeue(&q);

        if (temp->left == NULL)
        {
            temp->left = newNode;
            printf("Node inserted successfully.\n");
            return root;
        }
        else
        {
            enqueue(&q, temp->left);
        }

        if (temp->right == NULL)
        {
            temp->right = newNode;
            printf("Node inserted successfully.\n");
            return root;
        }
        else
        {
            enqueue(&q, temp->right);
        }
    }

    return root;
}



//recursive

//preorder Node.Left.Right

void recursive_preorder(struct tree *node)
{
    if (node == NULL)
        return;

    printf("%d ", node->data);

    recursive_preorder(node->left);
    recursive_preorder(node->right);
}

//inorder Left.Node.Right
void recursive_inorder(struct tree *node)
{
    if (node == NULL)
        return;

    recursive_inorder(node->left);

    printf("%d ", node->data);

    recursive_inorder(node->right);
}

//postorder Left.Right.Node
void recursive_postorder(struct tree *node)
{
    if (node == NULL)
        return;

    recursive_postorder(node->left);
    recursive_postorder(node->right);

    printf("%d ", node->data);
}

//iterative
//preorder Node.Left.Right
void iterative_preorder(struct tree *root)
{
    struct stack s;

    if (root == NULL)
        return;

    init_stack(&s);

    push(&s, root);

    while (!stack_is_empty(&s))
    {
        struct tree *node = pop(&s);

        printf("%d ", node->data);

        if (node->right != NULL)
            push(&s, node->right);

        if (node->left != NULL)
            push(&s, node->left);
    }
}

//inorder Left.Node.Right
void iterative_inorder(struct tree *root)
{
    struct stack s;
    struct tree *node = root;

    init_stack(&s);

    while (node != NULL || !stack_is_empty(&s))
    {
        while (node != NULL)
        {
            push(&s, node);
            node = node->left;
        }

        node = pop(&s);

        printf("%d ", node->data);

        node = node->right;
    }
}

//postorder Left.Right.Node
void iterative_postorder(struct tree *root)
{
    struct stack s;
    struct tree *node = root;
    struct tree *previous = NULL;
    init_stack(&s);
    while (node != NULL || !stack_is_empty(&s))
    {
        while (node != NULL)
        {
            push(&s, node);
            node = node->left;
        }

        node = peek(&s);
        if (node->right != NULL && node->right != previous)
        {
            node = node->right;
        }
        else
        {
            printf("%d ", node->data);
            previous = node;
            pop(&s);
            node = NULL;
        }
    }
}

//normal order level by level
void normal_order(struct tree *root)
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
        struct tree *node = dequeue(&q);
        printf("%d ", node->data);
        if (node->left != NULL)
            enqueue(&q, node->left);
        if (node->right != NULL)
            enqueue(&q, node->right);
    }
    printf("\n");
}

void recursive_menu()
{
    int choice;
    int attempts;
    char ch;

    while (1)
    {
        printf("\n");
        printf("RECURSIVE TRAVERSAL\n");
        printf("1. Preorder\n");
        printf("2. Inorder\n");
        printf("3. Postorder\n");
        printf("4. Back\n");

        attempts = 0;
        while (attempts < MAX_ATTEMPTS)
        {
            printf("Enter your choice: ");

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
                else if (choice < 1 || choice > 4)
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

        if (choice == 1)
        {
            printf("Recursive Preorder: ");
            recursive_preorder(root);
            printf("\n");
        }
        else if (choice == 2)
        {
            printf("Recursive Inorder: ");
            recursive_inorder(root);
            printf("\n");
        }
        else if (choice == 3)
        {
            printf("Recursive Postorder: ");
            recursive_postorder(root);
            printf("\n");
        }
        else if (choice == 4)
        {
            return;
        }
    }
}

void iterative_menu()
{
    int choice;
    int attempts;
    char ch;

    while (1)
    {
        printf("\n");
        printf("ITERATIVE TRAVERSAL\n");
        printf("1. Inorder\n");
        printf("2. Postorder\n");
        printf("3. Normal Order\n");
        printf("4. Preorder\n");
        printf("5. Back\n");

        attempts = 0;

        while (attempts < MAX_ATTEMPTS)
        {
            printf("Enter your choice: ");

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

        if (choice == 1)
        {
            printf("Iterative Inorder: ");
            iterative_inorder(root);
            printf("\n");
        }
        else if (choice == 2)
        {
            printf("Iterative Postorder: ");
            iterative_postorder(root);
            printf("\n");
        }
        else if (choice == 3)
        {
            printf("Normal Order: ");
            normal_order(root);
            printf("\n");
        }
        else if (choice == 4)
        {
            printf("Iterative Preorder: ");
            iterative_preorder(root);
            printf("\n");
        }
        else if (choice == 5)
        {
            return;
        }
    }
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
        printf("READ TREE\n");
        printf("1. Recursive Traversal\n");
        printf("2. Iterative Traversal\n");
        printf("3. Back\n");

        attempts = 0;

        while (attempts < MAX_ATTEMPTS)
        {
            printf("Enter your choice: ");

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
                else if (choice < 1 || choice > 3)
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

        if (choice == 1)
        {
            recursive_menu();
        }
        else if (choice == 2)
        {
            iterative_menu();
        }
        else if (choice == 3)
        {
            return;
        }
    }
}

void update_node()
{
    int old_value;
    int new_value;
    int valid;
    int attempts;
    char ch;
    struct queue q;
    struct tree *found = NULL;
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    old_value = getSearchValue(&valid);
    if (valid == 0)
        return;
    init_queue(&q);
    enqueue(&q, root);
    while (!queue_is_empty(&q))
    {
        struct tree *temp = dequeue(&q);
        if (temp->data == old_value)
        {
            found = temp;
            break;
        }
        if (temp->left != NULL)
            enqueue(&q, temp->left);
        if (temp->right != NULL)
            enqueue(&q, temp->right);
    }

    if (found == NULL)
    {
        printf("Value not found!\n");
        return;
    }

    attempts = 0;
    while (attempts < MAX_ATTEMPTS)
    {
        printf("Enter new value: ");
        if (scanf("%d", &new_value) != 1)
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
            else if (new_value == old_value)
            {
                printf("Invalid\n");
                attempts++;
            }
            else if (isValueExists(new_value))
            {
                printf("Invalid\n");
                attempts++;
            }
            else
            {
                found->data = new_value;
                printf("Node updated successfully.\n");
                return;
            }
        }
    }

    printf("Invalid\n");
}

void delete_node()
{
    int value, valid;
    struct queue q;
    struct tree *target = NULL;
    struct tree *last = NULL;
    struct tree *parent_last = NULL;

    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }
    value = getSearchValue(&valid);
    if (valid == 0)
        return;

    init_queue(&q);
    enqueue(&q, root);

    while (!queue_is_empty(&q))
    {
        struct tree *temp = dequeue(&q);

        if (temp->data == value)
            target = temp;

        if (temp->left != NULL)
        {
            enqueue(&q, temp->left);
            parent_last = temp;
            last = temp->left;
        }
        if (temp->right != NULL)
        {
            enqueue(&q, temp->right);
            parent_last = temp;
            last = temp->right;
        }
    }
    if (target == NULL)
    {
        printf("Value not found!\n");
        return;
    }
    if (last == NULL)  // Only root exists
    {
        free(root);
        root = NULL;
        printf("Node deleted successfully.\n");
        return;
    }
    target->data = last->data;   // Replace target’s data with last node’s data

    if (parent_last->left == last)
    {
        // Free last node directly
        parent_last->left = NULL;
    }  
    else
    {
        parent_last->right = NULL;
    }
    free(last);

    printf("Node deleted successfully.\n");
}

// while (!queue_is_empty(&q))
//     {
//         struct tree *temp = dequeue(&q);

//         if (temp->left == last)
//         {
//             free(temp->left);
//             temp->left = NULL;
//             break;
//         }
//         if (temp->right == last)
//         {
//             free(temp->right);
//             temp->right = NULL;
//             break;
//         }

//         if (temp->left != NULL)
//             enqueue(&q, temp->left);
//         if (temp->right != NULL)
//             enqueue(&q, temp->right);
//     }

//     printf("Node deleted successfully.\n");
// }

int main()
{
    int choice;
    int attempts;
    char ch;

    while (1)
    {
        printf("\n");
        printf("BINARY TREE CRUD\n");
        printf("\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update Node\n");
        printf("4. Delete Node\n");
        printf("5. Exit\n");

        attempts = 0;

        while (attempts < MAX_ATTEMPTS)
        {
            printf("Enter your choice: ");

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

        if (choice == 1)
        {
            root = create_node();
        }
        else if (choice == 2)
        {
            read_tree();
        }
        else if (choice == 3)
        {
            update_node();
        }
        else if (choice == 4)
        {
            delete_node();
        }
        else if (choice == 5)
        {
            printf("Program exited successfully.\n");
            break;
        }
    }

    return 0;
}