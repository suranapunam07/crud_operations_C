#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
    int rightThread;
};

struct tree *root = NULL;


/* Create a new node */
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


/* Check whether value already exists */
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


/* Insert a node */
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
    /* Insert on left side */
    if (value < parent->data)
    {
        newnode->right = parent;
        newnode->rightThread = 1;
        parent->left = newnode;
    }

    /* Insert on right side */
    else
    {
        newnode->right = parent->right;
        newnode->rightThread = 1;
        parent->right = newnode;
        parent->rightThread = 0;
    }
}


/* Find the leftmost node */
struct tree *leftmost(struct tree *node)
{
    if (node == NULL)
        return NULL;

    while (node->left != NULL)
        node = node->left;

    return node;
}


/* Find inorder successor */
struct tree *inorder_successor(struct tree *node)
{
    if (node == NULL)
        return NULL;

    if (node->rightThread == 1)
        return node->right;

    return leftmost(node->right);
}


/* Inorder traversal */
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


/* Search a node */
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


/* Delete a node */
void delete_node(int value)
{
    struct tree *parent;
    struct tree *current;
    struct tree *successor;
    struct tree *successor_parent;
    struct tree *child;

    parent = NULL;
    current = root;

    /* Find the node */
    while (current != NULL)
    {
        if (value == current->data)
            break;

        parent = current;

        if (value < current->data)
        {
            current = current->left;
        }
        else
        {
            if (current->rightThread == 1)
            {
                current = NULL;
            }
            else
            {
                current = current->right;
            }
        }
    }
    if (current == NULL)
    {
        printf("Value not found.\n");
        return;
    }

      // Node has two real children
    if (current->left != NULL &&
        current->rightThread == 0 &&
        current->right != NULL)
    {
        successor_parent = current;
        successor = current->right;

        while (successor->left != NULL)
        {
            successor_parent = successor;
            successor = successor->left;
        }

        current->data = successor->data;

        current = successor;
        parent = successor_parent;
    }


    /*
       Find the real child of current.

       A thread is NOT a child.
    */
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

    //Node has no real child
    if (child == NULL)
    {
          // Deleting root
        if (parent == NULL)
        {
            root = NULL;
        }

           //Current is left child
        else if (parent->left == current)
        {
            parent->left = NULL;
        }

           //Current is right child
        else
        {
            
              // Parent's right pointer becomes
               // a thread to current's successor.
            parent->right = current->right;
            parent->rightThread = 1;
        }

        free(current);
        printf("Node deleted successfully.\n");
        return;
    }

      // Node has one real child

       //If current has a left child
    
    if (current->left != NULL)
    {
        child = current->left;
    }

    
      // Otherwise current has a real right child
    else
    {
        child = current->right;
    }

      // Deleting root with one child
    
    if (parent == NULL)
    {
        root = child;

        /*
           If current had a left child,
           child's right thread should point
           to current's inorder successor.
        */
        if (current->left != NULL)
        {
            if (current->rightThread == 1)
            {
                child->right = current->right;
                child->rightThread = 1;
            }
        }

        free(current);
        printf("Node deleted successfully.\n");
        return;
    }


    /*
       Current is left child of parent
    */
    if (parent->left == current)
    {
        parent->left = child;

        /*
           If current had a left child,
           its successor is current's successor.
        */
        if (current->left != NULL &&
            current->rightThread == 1)
        {
            struct tree *temp;

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

    /*
       Current is right child of parent
    */
    else
    {
        parent->right = child;
        parent->rightThread = 0;
    }

    free(current);

    printf("Node deleted successfully.\n");
}


/* Update a node */
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
                inorder();
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