#include <stdio.h>
#include <stdlib.h>
#define MAX 20
struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
    int rightThread;
};

struct tree *root = NULL;


// Create a new node 
struct tree *create_node(int value)
{
    struct tree *newnode;

    newnode = (struct tree *)malloc(sizeof(struct tree));

    if (newnode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->rightThread = 0;
    return newnode;
}

// Check whether value already exists
int isValueExists(int value)
{
    struct tree *temp;
    temp = root;

    while (temp != NULL)
    {
        if (value == temp->data)
            return 1;

        if (value < temp->data)
        {
            temp = temp->left;
        }
        else
        {
            if (temp->rightThread == 1)
                return 0;

            temp = temp->right;
        }
    }

    return 0;
}


// Insert a node
void insert(int value)
{
    struct tree *newnode;
    struct tree *temp;
    struct tree *parent;

    if (isValueExists(value))
    {
        printf("Value already exists.\n");
        return;
    }

    newnode = create_node(value);

    if (newnode == NULL)
        return;

    if (root == NULL)
    {
        root = newnode;
        return;
    }

    temp = root;
    parent = NULL;

    while (temp != NULL)
    {
        parent = temp;
        if (value < temp->data)
        {
            if (temp->left == NULL)
                break;
            temp = temp->left;
        }
        else
        {
            if (temp->rightThread == 1)
                break;
            temp = temp->right;
        }
    }
    // Insert on left side 
    if (value < parent->data)
    {
        newnode->right = parent;
        newnode->rightThread = 1;
        parent->left = newnode;
    }

    // Insert on right side
    else
    {
        newnode->right = parent->right;
        newnode->rightThread = parent->rightThread;
        parent->right = newnode; 
        parent->rightThread = 0;
    }
}


// Find the leftmost node
struct tree *leftmost(struct tree *node)
{
    if (node == NULL)
        return NULL;

    while (node->left != NULL)
        node = node->left;

    return node;
}


// Find inorder successor
struct tree *inorder_successor(struct tree *node)
{
    if (node == NULL)
        return NULL;

    if (node->rightThread == 1)
        return node->right;

    return leftmost(node->right);
}


// Inorder traversal
void inorder()
{
    struct tree *temp;

    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return;
    }

    temp = leftmost(root);
    printf("Inorder: ");

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = inorder_successor(temp);
    }

    printf("\n");
}


// Normal Inorder Traversal
void inorder_traversal(struct tree *node)
{
    struct tree *stack[MAX];
    int top = -1;
    struct tree *temp;

    temp = node;

    while (temp != NULL || top != -1)
    {
        while (temp != NULL)
        {
            stack[++top] = temp;
            temp = temp->left;
        }

        temp = stack[top--];
        printf("%d ", temp->data);

        if (temp->rightThread == 0)
            temp = temp->right;
        else
            temp = NULL;
    }
}


// Preorder Traversal
void preorder_traversal(struct tree *node)
{
    struct tree *stack[MAX];
    int top = -1;
    struct tree *temp;

    if (node == NULL)
        return;

    stack[++top] = node;

    while (top != -1)
    {
        temp = stack[top--];
        printf("%d ", temp->data);

        if (temp->rightThread == 0 && temp->right != NULL)
            stack[++top] = temp->right;

        if (temp->left != NULL)
            stack[++top] = temp->left;
    }
}


// Postorder Traversal
void postorder_traversal(struct tree *node)
{
    struct tree *stack[MAX];
    int top = -1;
    struct tree *current;
    struct tree *lastVisited;
    struct tree *temp;

    current = node;
    lastVisited = NULL;

    while (current != NULL || top != -1)
    {
        if (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        else
        {
            temp = stack[top];

            if (temp->rightThread == 0 &&
                temp->right != NULL &&
                lastVisited != temp->right)
            {
                current = temp->right;
            }
            else
            {
                printf("%d ", temp->data);
                lastVisited = stack[top--];
            }
        }
    }
}

// Search a node
void search(int value)
{
    struct tree *temp;

    temp = root;

    while (temp != NULL)
    {
        if (value == temp->data)
        {
            printf("Value found.\n");
            return;
        }

        if (value < temp->data)
        {
            temp = temp->left;
        }
        else
        {
            if (temp->rightThread == 1)
                break;

            temp = temp->right;
        }
    }

    printf("Value not found.\n");
}


// Delete a node

void delete_node(int value)
{
    struct tree *parent;
    struct tree *current;
    struct tree *smallest;
    struct tree *smallest_parent;
    struct tree *child;
    struct tree *temp;

    parent = NULL;
    current = root;

    // Case 1: Find node
    while (current != NULL && current->data != value)
    {
        parent = current;

        if (value < current->data)
        {
            current = current->left;
        }
        else if (current->rightThread == 0)
        {
            current = current->right;
        }
        else
        {
            current = NULL;
        }
    }

    // Case 2: Node not found
    if (current == NULL)
    {
        printf("Value not found.\n");
        return;
    }

    // Case 3: Node has two children
    if (current->left != NULL &&
        current->rightThread == 0 &&
        current->right != NULL)
    {
        smallest_parent = current;
        smallest = current->right;

        while (smallest->left != NULL)
        {
            smallest_parent = smallest;
            smallest = smallest->left;
        }

        current->data = smallest->data;
        parent = smallest_parent;
        current = smallest;
    }

    // Case 4: Find real child
    if (current->left != NULL)
    {
        child = current->left;
    }
    else if (current->rightThread == 0 &&
             current->right != NULL)
    {
        child = current->right;
    }
    else
    {
        child = NULL;
    }

    // Case 5: Node is a leaf
    if (child == NULL)
    {
        if (parent == NULL)
        {
            root = NULL;
        }
        else if (parent->left == current)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = current->right;
            parent->rightThread = 1;
        }

        free(current);
        printf("Node deleted successfully.\n");
        return;
    }

    // Case 6: Node has one child
    // Find the child to reconnect
    if (current->left != NULL)
    {
        child = current->left;
    }
    else
    {
        child = current->right;
    }

    if (parent == NULL)
    {
        root = child;

        if (current->left != NULL &&
            current->rightThread == 1)
        {
            temp = child;

            while (temp->rightThread == 0 &&
                   temp->right != NULL)
            {
                temp = temp->right;
            }

            temp->right = current->right;
            temp->rightThread = 1;
        }

        free(current);
        printf("Node deleted successfully.\n");
        return;
    }

    if (parent->left == current)
    {
        parent->left = child;

        if (current->left != NULL &&
            current->rightThread == 1)
        {
            temp = child;

            while (temp->rightThread == 0 &&
                   temp->right != NULL)
            {
                temp = temp->right;
            }

            temp->right = current->right;
            temp->rightThread = 1;
        }
    }
    else
    {
        parent->right = child;
        parent->rightThread = 0;
    }

    // Case 7: Free deleted node
    free(current);
    printf("Node deleted successfully.\n");
}


// Update a node
void update_node(int oldValue, int newValue)
{
    if (!isValueExists(oldValue))
    {
        printf("Old value not found.\n");
        return;
    }

    if (isValueExists(newValue))
    {
        printf("New value already exists.\n");
        return;
    }

    delete_node(oldValue);
    insert(newValue);

    printf("Node updated successfully.\n");
}


/* Main function */
int main()
{
    int choice;
    int value;
    int oldValue;
    int newValue;
    int traversalChoice;

    while (1)
    {
        printf("\n");
        printf("========== RIGHT THREADED BST ==========\n");
        printf("1. Insert Node\n");
        printf("2. Read Tree\n");
        printf("3. Search Node\n");
        printf("4. Update Node\n");
        printf("5. Delete Node\n");
        printf("6. Exit\n");
        printf("=========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);

                insert(value);
                break;

            case 2:
                printf("\n========== READ TREE ==========\n");
                printf("1. Inorder Traversal\n");
                printf("2. Preorder Traversal\n");
                printf("3. Postorder Traversal\n");
                printf("===============================\n");

                printf("Enter your choice: ");
                scanf("%d", &traversalChoice);

                switch (traversalChoice)
                {
                    case 1:
                        printf("Inorder: ");
                        inorder_traversal(root);
                        printf("\n");
                        break;

                    case 2:
                        printf("Preorder: ");
                        preorder_traversal(root);
                        printf("\n");
                        break;

                    case 3:
                        printf("Postorder: ");
                        postorder_traversal(root);
                        printf("\n");
                        break;

                    default:
                        printf("Invalid choice.\n");
                }
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);

                search(value);
                break;

            case 4:
                printf("Enter old value: ");
                scanf("%d", &oldValue);

                printf("Enter new value: ");
                scanf("%d", &newValue);

                update_node(oldValue, newValue);
                break;
            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &value);

                delete_node(value);
                break;

            case 6:
                printf("Program ended.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}