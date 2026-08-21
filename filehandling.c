#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int readInt(char message[])
{
    char input[100];
    char extra;
    int value;

    while (1)
    {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            exit(0);
        }

        
        if (sscanf(input, "%d %c", &value, &extra) == 1)
        {
            return value;
        }

        printf("Invalid input!\n");
    }
}

int validName(char name[])
{
    int i;

    if (strlen(name) == 0)
    {
        return 0;
    }

    for (i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
        {
            return 0;
        }
    }

    return 1;
}

void readName(char name[], int size)
{
    while (1)
    {
        if (fgets(name, size, stdin) == NULL)
        {
            exit(0);
        }

        name[strcspn(name, "\n")] = '\0';

        if (validName(name))
        {
            return;
        }

        printf("Invalid name!\n");
        printf("Enter name again: ");
    }
}

int idExists(int searchID)
{
    FILE *fp;
    int id;
    char name[100];

    fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        return 0;
    }

    while (fscanf(fp, "%d %99[^\n]", &id, name) == 2)
    {
        if (id == searchID)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


int main()
{
    FILE *fp, *temp;

    int choice;
    int id;
    int search;
    int found;

    char name[100];

    while (1)
    {
        
        printf("       CRUD SYSTEM\n");
        

        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        choice = readInt("Enter your choice: ");

        switch (choice)
        {
            case 1:

                fp = fopen("data.txt", "a");

                if (fp == NULL)
                {
                    printf("Error opening file!\n");
                    break;
                }

                while (1)
                {
                    id = readInt("Enter ID: ");

                    if (idExists(id))
                    {
                        printf("ID already exists!\n");
                    }
                    else
                    {
                        break;
                    }
                }

                printf("Enter name: ");
                readName(name, sizeof(name));

                fprintf(fp, "%d %s\n", id, name);

                fclose(fp);

                printf("Record added successfully!\n");

                break;


            case 2:

                fp = fopen("data.txt", "r");

                if (fp == NULL)
                {
                    printf("No record found!\n");
                    break;
                }

                printf("\n");
                printf("ID\tName\n");
                printf("--------\n");

                while (fscanf(fp, "%d %99[^\n]", &id, name) == 2)
                {
                    printf("%d\t%s\n", id, name);
                }

                fclose(fp);

                break;

            case 3:

                fp = fopen("data.txt", "r");

                if (fp == NULL)
                {
                    printf("No record found!\n");
                    break;
                }

                temp = fopen("temp.txt", "w");

                if (temp == NULL)
                {
                    printf("Error creating temporary file!\n");
                    fclose(fp);
                    break;
                }

                search = readInt("Enter ID to Update: ");

                found = 0;

                while (fscanf(fp, "%d %99[^\n]", &id, name) == 2)
                {
                    if (id == search)
                    {
                        printf("Current name: %s\n", name);

                        printf("Enter new name: ");
                        readName(name, sizeof(name));

                        found = 1;
                    }

                    fprintf(temp, "%d %s\n", id, name);
                }

                fclose(fp);
                fclose(temp);

                if (found)
                {
                    printf("Record updated successfully!\n");
                }
                else
                {
                    printf("ID not found! No record was updated.\n");
                }
                break;

            case 4:

                fp = fopen("data.txt", "r");

                if (fp == NULL)
                {
                    printf("No record found!\n");
                    break;
                }

                temp = fopen("temp.txt", "w");

                if (temp == NULL)
                {
                    printf("Error creating temporary file!\n");
                    fclose(fp);
                    break;
                }

                search = readInt("Enter ID to Delete: ");

                found = 0;

                while (fscanf(fp, "%d %99[^\n]", &id, name) == 2)
                {
                    if (id == search)
                    {
                        found = 1;
                    }
                    else
                    {
                        fprintf(temp, "%d %s\n", id, name);
                    }
                }

                fclose(fp);
                fclose(temp);

                if (found)
                {
                    printf("Record deleted successfully!\n");
                }
                else
                {
                    printf("ID not found! No record was deleted.\n");
                }
                break;

            case 5:
                printf("Thank you!\n");
                exit(0);

            default:
                printf("Invalid choice! Please enter a number from 1 to 5.\n");
        }
    }

    return 0;
}