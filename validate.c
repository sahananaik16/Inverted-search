#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"inv_header.h"

/*read_and_validate function*/
int read_and_validate(int argc,char *argv[],Slist **head,Slist **tail)
{
    /*declaring str array*/
    char str[50];
    /*loop to check command line arguments*/
    for(int i=1;argv[i]!=0;i++)
    {
        /*copying the CLA argument to the string*/
        strcpy(str,argv[i]);
        /*extracting the token from the string*/
        char *name=strtok(str,".");
        name=strtok(NULL,".");
        /*condition to check whether all the files are text files*/
        if(strstr(argv[i],".txt")!=NULL && strcmp(name,"txt")==0)
        {
            /*opening the text files*/
            FILE *fptr=fopen(argv[i],"r");
            /*checking the prescence of file*/
            if(fptr!=NULL)
            {
                /*Moving cursor to the end of the file*/
                fseek(fptr, 0, SEEK_END); 
                /*Getting the file size*/
                int size = ftell(fptr);   
                /*condition to check the content of the file*/
                if(size!=0)
                {
                    /*checking duplicate files*/
                    int ret=duplicate(head,argv[i]);
                    if(ret==success)
                    {
                        /*inserting the filename to the list*/
                        int ret1 = insert_at_last(head,argv[i]);
                        if(ret1==failure)
                        {
                            /*prompting error message if file is failed to add to list*/
                            printf("\033[1;31m");
                            printf("adding %s file to list failed\n",argv[i]);
                            printf("\033[0m");
                            /*close the opened file*/
                            fclose(fptr);
                        }
                        /*prompting message that file added to the list successfully*/
                        printf("\033[1;32m");
                        printf("%s file is added to the list\n",argv[i]); 
                        printf("\033[0m");
                    }
                    else
                    {
                        /*prompting error message if file doesn't exist*/
                        printf("\033[1;31m");
                        printf("%s file already exist\n",argv[i]);
                        printf("\033[0m");
                    }
      
                }
                else
                {
                    /*prompting error message if file doesn't contains any content*/
                    printf("\033[1;31m");
                    printf("%s file doesn't have any content\n",argv[i]);
                    printf("\033[0m");
                }
                
            }
            else
            {
                /*prompting error message if file doesn't exist*/
                printf("\033[1;31m");
                printf("%s file doesn't exist\n",argv[i]);
                printf("\033[0m");
            }
            
        }
        else
        {
            /*prompting error message if file contains extension other than .txt*/
            printf("\033[1;31m");
            printf("%s file has invalid extension\n",argv[i]);
            printf("\033[0m");
        }
    }
    return success;
}

/*duplicate function call*/
int duplicate(Slist **head,char *filename)
{
    /*validating head*/
    if(*head==NULL)
    {
        return success;
    }
    /*creating temporary pointer and initializing with head*/
    Slist *temp=*head;
    /*traversing through list*/
    while(temp!=NULL)
    {
        /*condition to check duplicate filename*/
        if(strcmp(temp->str,filename)==0)
        {
            return failure;
        }
        /*updating temp*/
        temp=temp->link;
    }
    return success;
}


/*insert_at_last function*/
int insert_at_last(Slist **head, char *data)
{
    /*declaring pointer and initilazing it*/
    Slist *new=NULL;
    /*calling creat_node function*/
    int ret = create_node(&new,data);
    if(ret==failure)
    {
        return failure;
    }
    /*checking whether the head is NULL*/
    if(*head==NULL)
    {
        
        /*updating the head with node address*/ 
	    *head=new;
	    return success;
    }
    
    /*creating the temproary pointer*/
    Slist *temp = *head;
    
    /*loop to check the node link*/
    while(temp->link != NULL)
    {
        /*update the temp with temp link*/
 	    temp=temp->link;
    }
    /*update the last node link with new node*/
    temp->link=new;
    return success;
}

/*creat_node function*/
int create_node(Slist **new,char *data)
{
    /* Creating the new node */
	*new = malloc(sizeof(Slist));

	/* Check whether new node created or not */
	if (*new == NULL)
	{
		return failure;
	}

	/* updating the str and link of the node */
	strcpy((*new)->str,data);
	(*new)->link = NULL;
    return success;
}

/*print_list function*/
void print_list(Slist **head)
{

    /*checking whether the head is NULL or not*/
	if (*head == NULL)
	{
        printf("\033[1;31m");
	    /*print error message if list is empty*/
		printf("INFO : List is empty\n");
        printf("\033[0m");
	}
    else
    {
        printf("\033[1;33m");
        printf("Files from which data is saved in database :");
        printf("\033[0m");
        Slist *temp=*head;
        /*if head is NULL print the list using loop*/
	    while (temp!=NULL)		
	    {
            printf("\033[1;30m");
		    printf("%s ", temp -> str);
            printf("\033[0m");
		    temp = temp -> link;
	    }

	    printf("\n");
    }
}