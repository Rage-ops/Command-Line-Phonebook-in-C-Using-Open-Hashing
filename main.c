#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "phonebook.h"


int main()
{
    int choice;
    hash_init(table);
    printf("Phonebook using OpenHashing\n-----------------------------\n");
    do
    {
        printf("\n> Commands:\n1. Insert\n2. Delete\n3. List\n4. Update\n5. Search\n6. Total Contacts \n7. Terminate\n\nEnter your choice:\n");
        printf("> ");
        scanf(" %d", &choice);
        getchar();
        switch (choice)
        {
            case 1:
            {
                if (!insert())
                {
                    printf("\nError: Could not load the contact into the table\n");
                }
                else
                {
                    printf("\nLoaded the contact into the table\n");
                }
                break;
            }
            case 2:
            {
                char name[LENGTH + 1];
                printf("Enter name of the contact to be deleted: ");
                scanf("%[^\n]%*c", name);
                printf("\nEnter y to continue and any other key to abort:");
                char ch = getchar();
                if (ch == 'y')
                {
                    if (!delete(name))
                    {
                        printf("\nCould not delete the contact\n");
                    }
                    else
                    {
                        printf("\nDeleted the contact\n");
                    }
                }
                else
                {
                    printf("\nAborted Deletion\n");
                }
                break;
            }
            case 3:
            {
                display();
                break;
            }
            case 4:
            {
                char name[LENGTH + 1];
                printf("\nEnter name of the contact whose details is to be updated: ");
                scanf("%[^\n]%*c", name);
                int index = hash(name), res = search(name);
                if (res == 1)
                {
                    for (Node *temp = table[index]; temp != NULL; temp = temp->next)
                    {
                        if(strcmp(temp->name, name) == 0)
                        {
                            printf("\nContact Found!\n");
                            printf("\nDetails are:\nContact Name: %s\nPhno:%llu\n", temp->name, temp->phno);
                            int opt;
                            printf("Enter:\n1. Rename the contact\n2. Update Phone No\n3. Update Both\n>");
                            scanf(" %d", &opt);
                            if (opt == 2) // Updating just Phno
                            {
                                printf("\nEnter new phno:\n");
                                unsigned long long int phno;
                                scanf(" %llu", &phno);
                                temp->phno = phno;
                            }
                            else
                            {
                                unsigned long long int contact = temp->phno;
                                if (!delete(name)) // deleting the contact
                                {
                                    printf("\nUpdate Failed!\n");
                                    break;
                                }
                                printf("Enter new name:"); // new name
                                scanf(" %[^\n]%*c", name);
                                if (opt == 1) // renaming
                                {
                                    if (!load(name, contact))
                                    {
                                        printf("\nUpdate Failed!\n");   
                                        break;
                                    }
                                }
                                else if (opt == 3) // updating contact number and phno
                                {
                                    printf("\nEnter new phno:");
                                    unsigned long long int phno;
                                    scanf(" %llu", &phno);   
                                    if (!load(name, phno))
                                    {
                                        printf("\nUpdate Failed!\n");   
                                        break;
                                    }
                                }
                            }
                            printf("\nDetails Updated!\n");
                            break;
                        }
                    }
                }
                else if (res == 0)
                {
                    printf("\nContact not found!\n");   
                }
                break;
            }
            case 5:
            {
                char name[LENGTH + 1];
                printf("\nEnter name of the contact to be searched: ");
                scanf("%[^\n]%*c", name);
                int index = hash(name), res = search(name);
                if (res == 1) 
                {
                    for (Node *temp = table[index]; temp != NULL; temp = temp->next)
                    {
                        if(strcmp(temp->name, name) == 0)
                        {
                            printf("\nContact Found!\n");
                            printf("\nDetails are:\nContact Name: %s\nPhno:%llu\n", temp->name, temp->phno);
                            break;
                        }
                    }
                }
                else if (res == 0)
                {
                    printf("\nContact not Found!\n");
                }
                break;
            }
            case 6:
            {
                printf("\nNumber of contacts inserted : %lu\n", count());
                break;
            }
            case 7:
            {
                printf("\nTerminating the program!\n");
                unload(table);
                return 0;
            }
        }
    } while (choice >=1 && choice <= 7);
}