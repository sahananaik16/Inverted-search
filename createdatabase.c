#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
#include"inv_header.h"

/*create data base*/
int createdb(hash *arr, int argc, char *argv[], Slist *head, mnode **main, snode **sub)
{
    /*Buffer to store characters of a word*/
    char buff[20];  
    /*Character variable for reading file*/
    char ch;  
    /*Index to keep track of buffer position*/       
    int i = 0;      

    /* Loop through each file node in the Slist linked list */
    while (head != NULL)
    {
        /* Validate the file associated with the current node in Slist */
        int val = validate_file(head->str, arr);
        
        /* If file validation fails, move to the next node */
        if (val == failure)
        {
            head = head->link;
            continue;
        }

        /* Open the file in read mode */
        FILE *fptr = fopen(head->str, "r");

        /* Read each character in the file until the end of file is reached */
        while ((ch = getc(fptr)) != EOF)
        {
            /*Store the character in buffer*/
            buff[i] = ch;  

            /* Check if the character is a space or newline (end of word) */
            if (buff[i] == ' ' || buff[i] == '\n')
            {
                /*Null-terminate the buffer */
                buff[i] = '\0'; 

                /* Calling word_to_database function to add the word to the database */
                int ret = word_to_database(arr, buff, head, main, sub);
                
                /* If adding word fails, return failure */
                if (ret == failure)
                {
                    return failure;
                }
                /*Reset index to -1, so it becomes 0 after incrementing*/
                i = -1;  
            }
            /*Increment index for the next character*/ 
            i++;  
        }
        /*Close the file after reading*/
        fclose(fptr);  
        /*Move to the next file node in Slist*/
        head = head->link;  
    }
}

/*adding word to data base*/
int word_to_database(hash *HT, char *buff, Slist *head, mnode **main, snode **sub)
{
    /* Calculate index based on first character of the word */
    int index = tolower(buff[0]) % 97;

    /* If no main node exists at this index in the hash table */
    if (HT[index].link == NULL)
    {
        *main = NULL;
        *sub = NULL;

        /* Create a main node for the new word */
        int ret1 = createmnode(main, buff);
        if (ret1 == failure)
        {
            return failure;
        }

        /* Create a subnode for the filename in the Slist node */
        int ret2 = createsnode(main, head->str);
        if (ret2 == failure)
        {
            return failure;
        }

        /* Link the newly created main node to the hash table */
        HT[index].link = *main;
        return success;
    }

    /* Traverse main nodes at the current hash index */
    mnode *temp = HT[index].link;
    mnode *pre = NULL;
    
    while (temp != NULL)
    {
        pre = temp;

        /* If word already exists in the hash table */
        if (strcmp(temp->word, buff) == 0)
        {
            /* Check for filename in the subnodes */
            snode *temp1 = temp->subnode_link;
            while (temp1 != NULL)
            {
                /* If filename already exists, increment word count in that file */
                if (strcmp(temp1->f_name, head->str) == 0)
                {
                    temp1->wordcount++;
                    return success;
                }
                temp1 = temp1->sub_link;
            }

            /* If filename not found, create a new subnode for the filename */
            int ret3 = createsnode(&temp, head->str);
            if (ret3 == failure)
            {
                return failure;
            }

            /* Increment file count in main node */
            temp->filecount++;
            return success;
        }
        
        temp = temp->mainnode_link;
    }

    /* If the word was not found, create a new main node for the word */
    int ret4 = createmnode(&pre, buff);
    if (ret4 == failure)
    {
        return failure;
    }

    /* Move pre pointer to the newly created main node */
    pre = pre->mainnode_link;

    /* Create a subnode for the filename */
    int ret5 = createsnode(&pre, head->str);
    if (ret5 == failure)
    {
        return failure;
    }

    return success;
}

/*creating hash table*/
void create_HT(hash *HT)
{
    /*loop to create hashing table*/
    for(int i=0;i<28;i++)
    {
        /*updating index with i, value with -1 and link with NULL*/
        HT[i].key=i;
        HT[i].link=NULL;
    }
}

/*creating the main node*/
int createmnode(mnode **main, char *buff)
{
    /* Creating the new main node and allocating memory */
    mnode *new = malloc(sizeof(mnode));
    
    /* validating allocated memory*/
    if (new == NULL)
    {
        return failure;
    }

    /* Initializing the new node's data fields */

    /*Copy the word to the new node*/
    strcpy(new->word, buff);       
    /*Set the links to NULL*/
    new->mainnode_link = NULL;      
    new->subnode_link = NULL;       
    /*Initialize file count to 1*/
    new->filecount = 1;             

    /* If no main node exists in the list, make new node the head */
    if (*main == NULL)
    {
        *main = new;
        return success;
    }

    /* Traverse to the end of the main node list */
    mnode *temp = *main;
    while (temp->mainnode_link != NULL)
    {
        temp = temp->mainnode_link;
    }

    /* Link the new node to the last node in the main node list */
    temp->mainnode_link = new;
    return success;
}

/*creating the subnode*/
int createsnode(mnode **main, char *str)
{
    /* Allocate memory for the new subnode */
    snode *new = malloc(sizeof(snode));
    /*validating the allocated memory*/
    if (new == NULL)
    {
        return failure;
    }

    /* Initialize the new subnode fields */

    /*Copy the file name to the new node*/
    strcpy(new->f_name, str); 
    /*Set the next link of subnode as NULL*/   
    new->sub_link = NULL; 
    /*Initialize word count to 1*/       
    new->wordcount = 1;          

    /* If there are no subnodes linked to the main node, set this new node as the first subnode */
    if ((*main)->subnode_link == NULL)
    {
        (*main)->subnode_link = new;
        return success;
    }

    /* Traverse to the end of the subnode list */
    snode *temp = (*main)->subnode_link;
    while (temp->sub_link != NULL)
    {
        temp = temp->sub_link;
    }

    /* Link the new subnode at the end of the subnode list */
    temp->sub_link = new;
    return success;
}

/*validfating the files*/
int validate_file(char *str, hash *HT)
{
    /* Loop through the hash table */
    for(int i = 0; i < 28; i++)
    {
        /* Check if the current index has a linked list */
        if(HT[i].link != NULL)
        {
            mnode *main = HT[i].link;
            /* Iterate through the main nodes */
            while(main != NULL)
            {
                snode *sub = main->subnode_link;
                /* Iterate through the sub nodes */
                while(sub != NULL)
                {
                    /* Check if the file name matches */
                    if(strcmp(str, sub->f_name) == 0)
                    {
                        /*return if file already exists */
                        return failure; 
                    }
                    /* Move to the next sub node */
                    sub = sub->sub_link;
                }
                /* Move to the next main node */
                main = main->mainnode_link; 
            }
        }
    }
    /*return success if file is valid and does not exist in the database */
    return success; 
}
