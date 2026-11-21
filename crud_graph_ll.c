
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

struct node
{
    int vertex;
    struct node *next;
};

struct node *adj[MAX] = {NULL};
int vertices = 0;

int isValidVertex(int v)
{
    if (v < 1 || v > vertices)
        return 0;

    return 1;
}

struct node *createNode(int v)
{
    struct node *newnode;

    newnode = (struct node *)malloc(sizeof(struct node));

    if (newnode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newnode->vertex = v;
    newnode->next = NULL;

    return newnode;
}

int hasEdge(int u, int v)
{
    struct node *temp = adj[u - 1];

    while (temp != NULL)
    {
        if (temp->vertex == v)
            return 1;

        temp = temp->next;
    }

    return 0;
}

void addEdge(int u, int v)
{
    struct node *newnode;

    newnode = createNode(v);
    newnode->next = adj[u - 1];
    adj[u - 1] = newnode;

    newnode = createNode(u);
    newnode->next = adj[v - 1];
    adj[v - 1] = newnode;
}

void removeEdge(int u, int v)
{
    struct node *temp, *prev;

    temp = adj[u - 1];
    prev = NULL;

    while (temp != NULL)
    {
        if (temp->vertex == v)
        {
            if (prev == NULL)
                adj[u - 1] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            break;
        }

        prev = temp;
        temp = temp->next;
    }

    temp = adj[v - 1];
    prev = NULL;

    while (temp != NULL)
    {
        if (temp->vertex == u)
        {
            if (prev == NULL)
                adj[v - 1] = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            break;
        }

        prev = temp;
        temp = temp->next;
    }
}

// Create Vertex
void createVertex()
{
    if (vertices == MAX)
    {
        printf("Graph is full!\n");
        return;
    }

    adj[vertices] = NULL;
    vertices++;

    printf("Vertex %d added successfully.\n", vertices);
}

// Create Edge
void createEdge()
{
    int u, v;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter two vertex numbers (1 to %d): ", vertices);
    scanf("%d%d", &u, &v);

    if (!isValidVertex(u) || !isValidVertex(v))
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }

    if (hasEdge(u, v))
    {
        printf("Edge already exists!\n");
        return;
    }

    addEdge(u, v);

    printf("Edge added successfully.\n");
}

// Read Graph
void readGraph()
{
    int i, isolatedVertex = 0;
    struct node *temp;

    if (vertices == 0)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }

    for (i = 0; i < vertices; i++)
    {
        if (adj[i] == NULL)
        {
            isolatedVertex = 1;
            break;
        }
    }

    if (isolatedVertex == 1)
        printf("Some vertices are isolated.\n");

    printf("\nGraph Representation (Adjacency List):\n\n");

    for (i = 0; i < vertices; i++)
    {
        printf("%d -> ", i + 1);

        temp = adj[i];

        if (temp == NULL)
            printf("No connections");

        while (temp != NULL)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }

        printf("\n");
    }
}

// Update Edge
void updateEdge()
{
    int u, v, choice;

    if (vertices < 2)
    {
        printf("Add at least two vertices first.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (!isValidVertex(u) || !isValidVertex(v))
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }

    if (hasEdge(u, v))
    {
        printf("Edge already exists between %d and %d.\n", u, v);
        printf("1. Remove Edge\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            removeEdge(u, v);
            printf("Edge removed successfully.\n");
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
    else
    {
        printf("No edge exists between %d and %d.\n", u, v);
        printf("1. Add Edge\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            addEdge(u, v);
            printf("Edge added successfully.\n");
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }
}

// Delete Edge
void deleteEdge()
{
    int u, v;

    if (vertices < 2)
    {
        printf("At least two vertices are required.\n");
        return;
    }

    printf("Enter the two vertex numbers: ");
    scanf("%d%d", &u, &v);

    if (!isValidVertex(u) || !isValidVertex(v))
    {
        printf("Invalid vertex number!\n");
        return;
    }

    if (u == v)
    {
        printf("Self-loops are not allowed.\n");
        return;
    }

    if (!hasEdge(u, v))
    {
        printf("No edge exists between %d and %d.\n", u, v);
        return;
    }

    removeEdge(u, v);

    printf("Edge deleted successfully.\n");
}

// Delete Vertex
void deleteVertex()
{
    int v, i;
    struct node *temp, *prev, *nextnode;

    if (vertices == 0)
    {
        printf("Graph is empty.\n");
        return;
    }

    printf("Enter vertex number to delete (1 to %d): ", vertices);
    scanf("%d", &v);

    if (!isValidVertex(v))
    {
        printf("Invalid vertex number!\n");
        return;
    }

    // Remove all references to the deleted vertex
    for (i = 0; i < vertices; i++)
    {
        temp = adj[i];
        prev = NULL;

        while (temp != NULL)
        {
            if (temp->vertex == v)
            {
                if (prev == NULL)
                    adj[i] = temp->next;
                else
                    prev->next = temp->next;

                nextnode = temp->next;
                free(temp);
                temp = nextnode;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
    }

    // Free the deleted vertex's adjacency list
    temp = adj[v - 1];

    while (temp != NULL)
    {
        nextnode = temp->next;
        free(temp);
        temp = nextnode;
    }

    // Shift vertex head pointers
    for (i = v - 1; i < vertices - 1; i++)
        adj[i] = adj[i + 1];

    adj[vertices - 1] = NULL;

    // Renumber remaining vertices
    for (i = 0; i < vertices - 1; i++)
    {
        temp = adj[i];

        while (temp != NULL)
        {
            if (temp->vertex > v)
                temp->vertex--;

            temp = temp->next;
        }
    }

    vertices--;

    printf("Vertex deleted successfully.\n");
}

// Breadth First Search
void bfs(int start)
{
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int current;
    struct node *temp;

    visited[start - 1] = 1;
    queue[rear++] = start;

    printf("Breadth First Traversal: ");

    while (front < rear)
    {
        current = queue[front++];
        printf("%d ", current);

        temp = adj[current - 1];

        while (temp != NULL)
        {
            if (visited[temp->vertex - 1] == 0)
            {
                visited[temp->vertex - 1] = 1;
                queue[rear++] = temp->vertex;
            }

            temp = temp->next;
        }
    }

    printf("\n");
}

// Depth First Search
void dfs(int start)
{
    int visited[MAX] = {0};
    int stack[MAX];
    int top = -1;
    int current;
    struct node *temp;

    stack[++top] = start;
    visited[start - 1] = 1;

    printf("Depth First Traversal: ");

    while (top != -1)
    {
        current = stack[top--];
        printf("%d ", current);

        temp = adj[current - 1];

        while (temp != NULL)
        {
            if (visited[temp->vertex - 1] == 0)
            {
                visited[temp->vertex - 1] = 1;
                stack[++top] = temp->vertex;
            }

            temp = temp->next;
        }
    }

    printf("\n");
}

// Traversal Menu
void traversal()
{
    int choice, start;

    if (vertices == 0)
    {
        printf("Graph is empty. Create vertices first.\n");
        return;
    }

    printf("\n--- GRAPH TRAVERSAL MENU ---\n");
    printf("1. Breadth First Search (BFS)\n");
    printf("2. Depth First Search (DFS)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2)
    {
        printf("Invalid traversal choice!\n");
        return;
    }

    printf("Enter starting vertex (1 to %d): ", vertices);
    scanf("%d", &start);

    if (!isValidVertex(start))
    {
        printf("Invalid starting vertex!\n");
        return;
    }

    if (choice == 1)
        bfs(start);
    else
        dfs(start);
}

// Free all remaining memory
void freeGraph()
{
    int i;
    struct node *temp, *nextnode;

    for (i = 0; i < vertices; i++)
    {
        temp = adj[i];

        while (temp != NULL)
        {
            nextnode = temp->next;
            free(temp);
            temp = nextnode;
        }

        adj[i] = NULL;
    }
}

// Main Function
int main()
{
    int choice;

    do
    {
        printf("\n--- GRAPH CRUD MENU ---\n");
        printf("1. Create Vertex\n");
        printf("2. Create Edge\n");
        printf("3. Read Graph\n");
        printf("4. Update Edge\n");
        printf("5. Delete Edge\n");
        printf("6. Delete Vertex\n");
        printf("7. Graph Traversal\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createVertex();
                break;

            case 2:
                createEdge();
                break;

            case 3:
                readGraph();
                break;

            case 4:
                updateEdge();
                break;

            case 5:
                deleteEdge();
                break;

            case 6:
                deleteVertex();
                break;

            case 7:
                traversal();
                break;

            case 8:
                freeGraph();
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 8);

    return 0;
}
