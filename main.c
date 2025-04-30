#include<stdio.h>
#include<stdlib.h>
#include"inv_header.h"

int main(int argc, char *argv[])
{
    /* Declaring and initializing the head and tail pointers */
    Slist *head = NULL, *tail = NULL;
    int c;
    char op;
    /* Flags to check database creation and update status */
    int flag = 0, flag1 = 0; 
    /* Pointer for main nodes in the hash table */
    mnode *main; 
    /* Pointer for sub nodes in the hash table */
    snode *sub; 
    /* Hash table to store the database */
    hash arr[28]; 
    
    /* Creating the hash table */
    create_HT(arr);

    /* Argument count should be more than 1 */
    if(argc > 1)
    {
        /* Read and validate function */
        int ret = read_and_validate(argc, argv, &head, &tail);
        
        /* Validating the return value of read_and_validate function */
        if(ret != success)
        {
            /* Return failure if validation fails */
            return failure; 
        }

        /* Printing the list */
        print_list(&head);

        /* Menu loop */
        do
        {
            printf("\033[1;35m");
            printf("MENU:\n1.Create database\n2.Display database\n3.Search database\n4.Save database\n5.Update database\n6. Exit\n");
            printf("\033[0m");
            printf("\033[1;34m");
            printf("Enter the choice: ");
            printf("\033[0m");
            scanf("%d", &c);

            /* Switch case for handling menu options */
            switch(c)
            {
                case 1:
                    if(flag == 0)
                    {
                        /* Set flag to indicate database has been created */
                        flag = 1; 
                        /*calling createdb function*/
                        int ret1 = createdb(arr, argc, argv, head, &main, &sub);
                        if(ret1 == failure)
                        {
                            /* Return failure if database creation fails */
                            return failure; 
                        }
                        printf("\033[1;32m");
                        printf("Database created successfully\n");
                        printf("\033[0m");
                    }
                    else
                    {
                        printf("\033[1;31m");   
                        printf("Database already created\n");
                        printf("\033[0m");
                    }
                    break;

                case 2:
                    /* Display the database */
                    displaydb(arr); 
                    break;

                case 3:
                    /* Search the database */
                    searchdb(arr); 
                    break;

                case 4:
                    /*save database*/
                    int ret3 = savedb(arr);
                    if(ret3 == failure)
                    {
                        /* Return failure if saving the database fails */
                        return failure; 
                    }
                    printf("\033[1;32m");
                    printf("Data base saved successfully\n");
                    printf("\033[0m");
                    break;

                case 5:
                    if(flag1 == 0 && flag == 0)
                    {
                        /* Set flag to indicate database has been updated */
                        flag1 = 1; 
                        /* Update the database */
                        int ret4 =updatedb(arr); 
                        if(ret4 == failure)
                        {
                        /* Return failure if updating the database fails */
                        return failure; 
                        }
                    }
                    else
                    {
                        printf("\033[1;31m");
                        /* Printing error message if database already updated*/
                        printf("Database already updated or created\n");
                        printf("\033[0m");
                    }
                    break;

                case 6:
                    /* Exit the program */
                    printf("Exiting..\n");
                    exit(0); 
                    break;

                default:
                    printf("\033[1;31m");
                    /* Handle invalid menu option */
                    printf("Invalid choice!\n"); 
                    printf("\033[0m");
                    break;
            }
            printf("\033[1;30m");
            printf("Do you want to continue?\n");
            printf("If yes enter y/Y or enter n/N to discontinue: ");
            getchar();
            scanf("%c",&op);
            printf("\033[0m");
        } while(op == 'y' || op== 'y');

        printf("Exiting..\n");
        return success;
        
    }
    else
    {
        /* Prompting error message if argument count is less than 1 */
        printf("\033[1;31m");
        printf("ERROR:\nInvalid number of arguments!!\nCLA should be: ./a.out filename.txt ...\n");
        printf("\033[0m");
        /* Return failure if invalid argument count */
        return failure; 
    }
}
