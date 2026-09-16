#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_ATTEMPTS 3

unsigned int readUnsignedInt(char message[])
{
    char input[100];
    unsigned long int value;
    char extra;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("%s", message);

        if (fgets(input, sizeof(input), stdin) == NULL)
            exit(0);

        if (sscanf(input, "%lu %c", &value, &extra) == 1)
        {
            if (value <= UINT_MAX)
                return value;
        }

        attempts++;
        printf("Invalid\n");
    }

    printf("Returning to main menu...\n");
    return UINT_MAX;
}

int validName(char name[])
{
    int i;

    if (strlen(name) == 0)
        return 0;

    for (i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
            return 0;
    }

    return 1;
}

int readName(char name[], int size)
{
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        if (fgets(name, size, stdin) == NULL)
            exit(0);

        name[strcspn(name, "\n")] = '\0';

        if (validName(name))
            return 1;

        attempts++;
        printf("Invalid\n");
    }

    printf("Returning to main menu...\n");
    return 0;
}

float readMarks(char message[])
{
    float marks;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS)
    {
        printf("%s", message);

        if (scanf("%f", &marks) != 1)
        {
            printf("Invalid\n");

            while (getchar() != '\n');

            attempts++;
        }
        else if (marks < 0 || marks > 100)
        {
            printf("Invalid\n");

            while (getchar() != '\n');

            attempts++;
        }
        else
        {
            while (getchar() != '\n');
            return marks;
        }
    }

    printf("Returning to main menu...\n");
    return -1;
}

int idExists(unsigned int searchID)
{
    FILE *fp;
    unsigned int id;
    float marks;
    char name[100];

    fp = fopen("data.txt", "r");

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%u %f %[^\n]", &id, &marks, name) == 3)
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

int fileHasRecords()
{
    FILE *fp;
    unsigned int id;
    float marks;
    char name[100];

    fp = fopen("data.txt", "r");

    if (fp == NULL)
        return 0;

    if (fscanf(fp, "%u %f %[^\n]", &id, &marks, name) == 3)
    {
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}

int main()
{
    FILE *fp, *temp;

    unsigned int id, search;
    float marks;

    int found, choice, attempts;

    char name[100], line[256];

    while (1)
    {
        printf("\nCRUD SYSTEM\n");
        printf("1. Create\n");
        printf("2. Read\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        choice = readUnsignedInt("Enter your choice: ");

        if (choice == UINT_MAX)
            continue;

        switch (choice)
        {
            case 1:

                fp = fopen("data.txt", "a");

                if (fp == NULL)
                {
                    printf("Invalid\n");
                    break;
                }

                attempts = 0;

                while (attempts < MAX_ATTEMPTS)
                {
                    id = readUnsignedInt("Enter ID: ");

                    if (id == UINT_MAX)
                    {
                        fclose(fp);
                        break;
                    }

                    if (id == 0 || idExists(id))
                    {
                        attempts++;
                        printf("Invalid\n");
                    }
                    else
                    {
                        break;
                    }
                }

                if (attempts == MAX_ATTEMPTS || id == UINT_MAX)
                {
                    fclose(fp);
                    printf("Returning to main menu...\n");
                    break;
                }

                printf("Enter name: ");

                if (!readName(name, sizeof(name)))
                {
                    fclose(fp);
                    break;
                }

                marks = readMarks("Enter Marks: ");

                if (marks == -1)
                {
                    fclose(fp);
                    break;
                }

                fprintf(fp, "%u %.2f %s\n", id, marks, name);

                fclose(fp);

                printf("Record added!\n");

                break;


            case 2:

                fp = fopen("data.txt", "r");

                if (fp == NULL)
                {
                    printf("No records found!\n");
                    break;
                }

                printf("\nID\tName\tMarks\n");
                printf("---------------------------\n");

                found = 0;

                while (fgets(line, sizeof(line), fp))
                {
                    if (sscanf(line, "%u %f %[^\n]", &id, &marks, name) == 3)
                    {
                        name[strcspn(name, "\r")] = '\0';

                        printf("%u\t%s\t%.2f\n", id, name, marks);

                        found = 1;
                    }
                }

                if (!found)
                    printf("No records found!\n");

                fclose(fp);

                break;


            case 3:

                if (!fileHasRecords())
                {
                    printf("No records available to update!\n");
                    break;
                }

                fp = fopen("data.txt", "r");
                temp = fopen("temp.txt", "w");

                if (fp == NULL || temp == NULL)
                {
                    printf("Invalid\n");

                    if (fp)
                        fclose(fp);

                    if (temp)
                        fclose(temp);

                    break;
                }

                attempts = 0;
                found = 0;

                while (attempts < MAX_ATTEMPTS)
                {
                    search = readUnsignedInt("Enter ID to Update: ");

                    if (search == UINT_MAX)
                    {
                        fclose(fp);
                        fclose(temp);

                        remove("temp.txt");

                        break;
                    }

                    rewind(fp);

                    found = 0;

                    while (fgets(line, sizeof(line), fp))
                    {
                        if (sscanf(line, "%u %f %[^\n]", &id, &marks, name) == 3)
                        {
                            if (id == search)
                            {
                                found = 1;
                                break;
                            }
                        }
                    }

                    if (found)
                        break;

                    attempts++;

                    printf("Invalid\n");
                }

                if (!found)
                {
                    fclose(fp);
                    fclose(temp);

                    remove("temp.txt");

                    printf("Returning to main menu...\n");

                    break;
                }

                rewind(fp);

                while (fgets(line, sizeof(line), fp))
                {
                    if (sscanf(line, "%u %f %[^\n]", &id, &marks, name) == 3)
                    {
                        if (id == search)
                        {
                            printf("Enter new name: ");

                            if (!readName(name, sizeof(name)))
                            {
                                fclose(fp);
                                fclose(temp);

                                remove("temp.txt");

                                found = 0;

                                break;
                            }

                            marks = readMarks("Enter new marks: ");

                            if (marks == -1)
                            {
                                fclose(fp);
                                fclose(temp);

                                remove("temp.txt");

                                found = 0;

                                break;
                            }
                        }

                        fprintf(temp, "%u %.2f %s\n", id, marks, name);
                    }
                }

                if (found)
                {
                    fclose(fp);
                    fclose(temp);

                    remove("data.txt");
                    rename("temp.txt", "data.txt");

                    printf("Record updated!\n");
                }

                break;


            case 4:

                if (!fileHasRecords())
                {
                    printf("No records available to delete!\n");
                    break;
                }

                fp = fopen("data.txt", "r");
                temp = fopen("temp.txt", "w");

                if (fp == NULL || temp == NULL)
                {
                    printf("Invalid\n");

                    if (fp)
                        fclose(fp);

                    if (temp)
                        fclose(temp);

                    break;
                }

                attempts = 0;
                found = 0;

                while (attempts < MAX_ATTEMPTS)
                {
                    search = readUnsignedInt("Enter ID to Delete: ");

                    if (search == UINT_MAX)
                    {
                        fclose(fp);
                        fclose(temp);

                        remove("temp.txt");

                        break;
                    }

                    rewind(fp);

                    found = 0;

                    while (fgets(line, sizeof(line), fp))
                    {
                        if (sscanf(line, "%u %f %[^\n]", &id, &marks, name) == 3)
                        {
                            if (id == search)
                            {
                                found = 1;
                                break;
                            }
                        }
                    }

                    if (found)
                        break;

                    attempts++;

                    printf("Invalid\n");
                }

                if (!found)
                {
                    fclose(fp);
                    fclose(temp);

                    remove("temp.txt");

                    printf("Returning to main menu...\n");

                    break;
                }

                rewind(fp);

                while (fgets(line, sizeof(line), fp))
                {
                    if (sscanf(line, "%u %f %[^\n]", &id, &marks, name) == 3)
                    {
                        if (id != search)
                        {
                            fprintf(temp, "%u %.2f %s\n", id, marks, name);
                        }
                    }
                }

                fclose(fp);
                fclose(temp);

                remove("data.txt");
                rename("temp.txt", "data.txt");

                printf("Record deleted!\n");

                break;


            case 5:

                printf("Exiting...\n");

                return 0;


            default:

                printf("Invalid choice!\n");
        }
    }

    return 0;
}