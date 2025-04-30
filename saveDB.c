#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"inv_header.h"

/*saving data base*/
int savedb(hash *HT)
{
    char str[20];
    /* Prompting the user for the filename where the database should be saved */
    printf("\033[1;35m");
    printf("Enter the filename where database should be saved: ");
    printf("\033[0m");
    /*reading file name from user*/
    scanf("%s", str);
    
    /* Checking if the filename has .txt extension */
    if (strstr(str, ".txt") == NULL)
    {
        printf("\033[1;31m");
        printf("File extension should be .txt!!\n");
        printf("\033[0m");
        return failure;
    }
    
    /* Opening the file for writing */
    FILE *fptr = fopen(str, "w");
    int flag = 0;
    
    /* Iterating through the hash table */
    for (int i = 0; i < 28; i++)
    {
        if (HT[i].link != NULL)
        {
            /*traversing through main nodes*/
            mnode *main = HT[i].link; 
            while (main != NULL)
            {
                /* Check if the main node has sub-nodes */
                if (main->subnode_link != NULL)
                { 
                    /* Setting flag to indicate that data will be saved */
                    flag = 1; 
                    snode *sub = main->subnode_link;
                    /* Writing the main node's data to the file */
                    fprintf(fptr, "#%d;%s;%d;", i, (main)->word, (main)->filecount);
                    while (sub != NULL)
                    {
                        /* Writing sub-node data to the file */
                        fprintf(fptr, "%s;%d;", (sub)->f_name, (sub)->wordcount);  
                        sub = sub->sub_link;
                    }
                }
                /* Ending the current main node's data */
                fprintf(fptr, "#\n"); 
                /* Moving to the next main node */
                main = main->mainnode_link; 
            }  
        }
    }
    
    /* Closing the file */
    fclose(fptr);
    return success; 
}
