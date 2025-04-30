#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
#include"inv_header.h"

/*searching data in data base*/
int searchdb(hash *HT)
{
    char str[20];
    /* Prompting the user to enter the word to be searched */
    printf("\033[1;35m");
    printf("Enter the word to be searched: ");
    printf("\033[0m");
    /*reading word from user*/
    scanf("%s", str);
    
    /* Calculating the index based on the first character of the word */
    int index = tolower(str[0]) % 97;

    /* Checking if there is a linked list at the calculated index */
    if (HT[index].link != NULL)
    {
        /* Pointer to traverse the linked list */
        mnode *temp = HT[index].link; 
        
        /* Iterating through the main nodes at the calculated index */
        while (temp != NULL)
        {
            printf("\033[1;36m");
            /* Comparing the input word with the current node's word */
            if (strcmp(str, temp->word) == 0)
            {
                /* Printing the found word and its file count */
                printf("%s\t%d\t", str, temp->filecount);
                /* Pointer to traverse sub-nodes */
                snode *temp1 = temp->subnode_link; 
                
                /* Iterating through the sub-nodes to print their details */
                while (temp1 != NULL)
                {
                    /*printing subnode data*/
                    printf("%s\t%d\t", temp1->f_name, temp1->wordcount);  
                    /* Moving to the next sub-node */
                    temp1 = temp1->sub_link; 
                }
                printf("\n");
                printf("\033[0m");
                /* Indicating successful search */
                return success; 
            }
            /* Moving to the next main node */
            temp = temp->mainnode_link; 
        }
        
        /* If the word is not found in the linked list */
        printf("\033[1;31m");
        printf("Word not found!!\n");
        printf("\033[0m");
        return failure;
    }
    else
    {
        /* If there is no linked list at the index, the word cannot be found */
        printf("\033[1;31m");
        printf("Word not found!!\n");
        printf("\033[0m");
        return failure;
    }
}
