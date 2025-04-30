#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"inv_header.h"

/*displaying data base*/
void displaydb(hash *HT)
{
    /*Flag to check if any entries are present in the hash table*/
    int flag = 0,c=0;  
    for (int i = 0; i < 28; i++)
    {
        if (HT[i].link == NULL)
        ++c;
    }
    if (c == 28)
    {
        printf("\033[1;31m");   
        printf("Hash table is empty!!\n");
        printf("\033[0m");
        return;
    }
    printf("Index\tWord\tFile count\tFilename\tFile count\n");
    /* Loop through each index of the hash table */
    for (int i = 0; i < 28; i++)
    {
        /* Check if the current hash table index has any main nodes */
        if (HT[i].link != NULL)
        {
            /*Set main to the head of the main nodes list*/
            mnode *main = HT[i].link;  

            /* Traverse through the main nodes at this index */
            while (main != NULL)
            {
                /*Set flag to 1, indicating the hash table has data*/
                flag = 1;  
                /*Set sub to the head of the sub nodes list*/
                snode *sub = main->subnode_link; 
                printf("\033[1;36m");
                /* Print main node data: index, word, and file count */
                printf("[%d]\t%s\t%d\t", i, main->word, main->filecount);

                /* Traverse and print all sub nodes associated with this main node */
                while (sub != NULL)
                {
                    /*Print file name and word count*/
                    printf("\t%s\t\t%d\t", sub->f_name, sub->wordcount);
                    /*Move to the next sub node*/  
                    sub = sub->sub_link;  
                }

                printf("\n");  
                printf("\033[0m");
                /*Move to the next main node*/
                main = main->mainnode_link;  
            }
        }
    }
    
    /* If no entries were found, print that the hash table is empty */
    
}
