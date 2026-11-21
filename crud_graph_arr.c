#include <stdio.h>
#define MAX 20

int graph[MAX][MAX] = {0};
int vertices = 0;

// Check whether vertex number is valid
int isValidVertex(int v)
{
    if (v < 1 || v > vertices)
        return 0;

    return 1;
}

// Check whether graph is connected
int isGraphConnected()
{
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int current, i;

    if (vertices == 0)
        return 0;

    visited[0] = 1;
    queue[rear++] = 0;

    while (front < rear)
    {
        current = queue[front++];

        for (i = 0; i < vertices; i++)
        {
            if (graph[current][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    for (i = 0; i < vertices; i++)
    {
        if (visited[i] == 0)
            return 0;
    }

    return 1;
}

// Create Vertex
void createVertex()
{
    if (vertices == MAX)
    {
        printf("Graph is full!\n");
        return;
    }

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

    if (graph[u - 1][v - 1] == 1)
    {
        printf("Edge already exists!\n");
        return;
    }

    graph[u - 1][v - 1] = 1;
    graph[v - 1][u - 1] = 1;

    printf("Edge added successfully.\n");
}

// Read Graph
void readGraph()
{
    int i, j;

    if (vertices == 0)
    {
        printf("Graph is empty. No vertices exist.\n");
        return;
    }

    if (!isGraphConnected())
    {
        printf("Graph does not exist as a connected graph.\n");
        printf("Graph representation cannot be displayed.\n");
        return;
    }

    printf("\nGraph Representation (Adjacency List):\n\n");

    for (i = 0; i < vertices; i++)
    {
        printf("%d -> ", i + 1);

        for (j = 0; j < vertices; j++)
        {
            if (graph[i][j] == 1)
                printf("%d ", j + 1);
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

    if (graph[u - 1][v - 1] == 1)
    {
        printf("Edge already exists between %d and %d.\n", u, v);
        printf("1. Remove Edge\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            graph[u - 1][v - 1] = 0;
            graph[v - 1][u - 1] = 0;
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
            graph[u - 1][v - 1] = 1;
            graph[v - 1][u - 1] = 1;
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

    if (graph[u - 1][v - 1] == 0)
    {
        printf("No edge exists between %d and %d.\n", u, v);
        return;
    }

    graph[u - 1][v - 1] = 0;
    graph[v - 1][u - 1] = 0;

    printf("Edge deleted successfully.\n");
}

// Delete Vertex
void deleteVertex()
{
    int v, i, j;

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

    v--;

    for (i = v; i < vertices - 1; i++)
    {
        for (j = 0; j < vertices; j++)
        {
            graph[i][j] = graph[i + 1][j];
        }
    }

    for (j = v; j < vertices - 1; j++)
    {
        for (i = 0; i < vertices - 1; i++)
        {
            graph[i][j] = graph[i][j + 1];
        }
    }

    vertices--;

    for (i = 0; i < MAX; i++)
    {
        graph[vertices][i] = 0;
        graph[i][vertices] = 0;
    }

    printf("Vertex deleted successfully.\n");
}

// Breadth First Search
void bfs(int start)
{
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;
    int current, i;

    visited[start] = 1;
    queue[rear++] = start;

    printf("Breadth First Traversal: ");

    while (front < rear)
    {
        current = queue[front++];
        printf("%d ", current + 1);

        for (i = 0; i < vertices; i++)
        {
            if (graph[current][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");
}

// Depth First Search
void dfs_visit(int vertex, int visited[])
{
    int i;

    visited[vertex] = 1;
    printf("%d ", vertex + 1);

    for (i = 0; i < vertices; i++)
    {
        if (graph[vertex][i] == 1 && visited[i] == 0)
        {
            dfs_visit(i, visited);
        }
    }
}

void dfs(int start)
{
    int visited[MAX] = {0};
    int stack[MAX];
    int top = -1;
    int current, i;

    stack[++top] = start;

    printf("Depth First Traversal: ");

    while (top != -1)
    {
        current = stack[top--];

        if (visited[current] == 1)
            continue;

        visited[current] = 1;
        printf("%d ", current + 1);

        for (i = vertices - 1; i >= 0; i--)
        {
            if (graph[current][i] == 1 && visited[i] == 0)
            {
                stack[++top] = i;
            }
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

    if (!isGraphConnected())
    {
        printf("Graph does not exist as a connected graph.\n");
        printf("Traversal is not possible.\n");
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

    start--;

    if (choice == 1)
        bfs(start);
    else
        dfs(start);
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
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 8);

    return 0;
}