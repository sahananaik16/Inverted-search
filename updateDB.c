#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
#include"inv_header.h"

/*update database function*/
int updatedb(hash *HT)
{
    /*declaring string*/
    char str[20];
    /*prompt message to user to enter the saved filename*/
    printf("\033[1;35m");
    printf("Enter the saved filename: ");
    printf("\033[0m");
    /*reading string from user*/
    scanf("%s",str);
    /*validating extension of the file*/
    if(strstr(str,".txt")==NULL)
    {
        printf("\033[1;31m");
        printf("File extension should be .txt!!\n");
        printf("\033[0m");
        return failure;
    }
    /*opening file to read the content*/
    FILE *fptr=fopen(str,"r");
    /*validating the file presence*/
    if(fptr==NULL)
    {
        printf("\033[1;31m");
        printf("File don't exist\n");
        printf("\033[0m");
        return failure;
    }
    
    char ch;
    int flag=0;
    /*reading content from the file and checking whether file content is starting and ending with # */
    if((ch=getc(fptr))=='#')
    {
        fseek(fptr, -2, SEEK_END);
        if((ch=getc(fptr))=='#')
        {
            /*updating flag when file content starting and ending with #*/
            flag=1;
        }
    }
    /*if flag not updated print error message*/
    if(flag==0)
    {
        printf("\033[1;31m");
        printf("File content should start and end with '#'");
        printf("\033[0m");
        return failure;
    }
    /*rewinding the pointer to starting of file*/
    rewind(fptr);
    char arr[100];
    int i=0;
    /*loop to read content of the file*/
    while((ch=getc(fptr))!=EOF)
    {
        /*copying read caharcter in the string*/
        arr[i]=ch;
        /*if ch is new line end copying and put NULL character at end of the string*/
        if(arr[i]=='\n')
        {
            arr[i]='\0';
            /*calling file_to_database function*/
            file_to_database(arr,HT);
            /*re initializing string to stotre new line*/
            i=-1;
        }
        i++;
    }
    printf("\033[1;32m");
    printf("updating successfull\n");
    printf("\033[0m");
    return success;
}

/*file_to_database function*/
int file_to_database(char *arr, hash *HT)
{
    /* Extract the first token and convert it to an index */
    char *tok = strtok(arr, "#;");
    /*Convert token to integer index*/
    int index = atoi(tok);  
    
    /* Extract the buffer token, return failure if NULL */
    char *buff = strtok(NULL, ";");
    if (buff == NULL) 
        return failure; 
    
    mnode *main;
    snode *sub;

    /* Check if the hash table at index is empty */
    if (HT[index].link == NULL)
    {
        main = NULL;
        sub = NULL;

        /* Create and initialize the main node */
        int ret1 = createmnode_upd(&main, buff);
        if (ret1 == failure)
        {
            return failure;
        }

        /* Link the newly created main node to the hash table index */
        HT[index].link = main;
        return success;
    }
    /*if hash table is not empty*/
    else
    {
        /* Traverse to the end of the mainnode linked list */
        mnode *temp = HT[index].link;
        while (temp->mainnode_link != NULL)
        {
            temp = temp->mainnode_link;
        }

        /* Create and link a new main node at the end of the list */
        int ret1 = createmnode_upd(&temp, buff);
        if (ret1 == failure)
        {
            return failure;
        }
        
        return success;
    }
}

/*createmnode_upd function*/
int createmnode_upd(mnode **main, char *buff)
{
    /* Creating the new main node */
    mnode *new = malloc(sizeof(mnode));
    
    /* validating memory allocation*/
    if (new == NULL)
    {
        return failure;
    }
    
    /* Extract file count from the next token and initialize the new node */
    char *fc = strtok(NULL, ";");
    /*Copy buff string to new node's word*/
    strcpy(new->word, buff); 
    /*Initialize links to NULL*/    
    new->mainnode_link = NULL;    
    new->subnode_link = NULL;
    /* Convert file count to integer*/
    new->filecount = atoi(fc);     
    int i = new->filecount;         

    /* If main node list is empty, assign new node as the first node */
    if (*main == NULL)
    {
        *main = new;
        
        /* Create subnodes as per file count */
        while (i > 0)
        {
            /*createsnode_upd function call*/
            int ret2 = createsnode_upd(&new);
            if (ret2 == failure)
            {
                /*Return failure if subnode creation fails*/
                return failure;    
            }
            i--;
        }
        return success;
    }
    
    /* Traverse to the last node in the main node list */
    mnode *temp = *main;
    while (temp->mainnode_link != NULL)
    {
        temp = temp->mainnode_link;
    }

    /* Add the new node at the end of the main node list */
    temp->mainnode_link = new;

    /* Create subnodes for the new main node */
    while (i > 0)
    {
        /*createsnode_upd function call*/
        int ret2 = createsnode_upd(&new);
        if (ret2 == failure)
        {
            /*Return failure if subnode creation fails*/
            return failure;
        }
        i--;
    }

    return success;
}

/*createsnode_upd function*/
int createsnode_upd(mnode **main)
{
    /* Extract file name and word count from the tokens */
    char *str = strtok(NULL, ";");   
    char *wc = strtok(NULL, ";");    

    /* Allocate memory for a new subnode */
    snode *new = malloc(sizeof(snode));
    if (new == NULL)
    {
        /*Return failure if memory allocation fails*/
        return failure;
    }

    /* Initialize new subnode fields */

    /*Copy file name to subnode*/
    strcpy(new->f_name, str);  
    /*Initialize sub_link to NULL*/         
    new->sub_link = NULL;
    /*Convert word count to integer*/
    new->wordcount = atoi(wc);

    /* If there are no existing subnodes, set new subnode as the first subnode */
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

    /* Insert the new subnode at the end of the list */
    temp->sub_link = new;
    return success;
}

