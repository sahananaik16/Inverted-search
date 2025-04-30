#ifndef TYPES_H
#define TYPES_H

/* Defining return status codes */
#define success 0
#define failure -1

/* Structure for single linked list nodes */
typedef struct node
{
	/* String data */
    char str[50]; 
	/* Pointer to the next node */
    struct node *link; 
} Slist;

/* Structure for sub-nodes in the hash table */
typedef struct sub_node
{
	/* Count of words */
    int wordcount; 
	/* Filename associated with the word */
    char f_name[50]; 
	/* Pointer to the next sub-node */
    struct sub_node *sub_link; 
} snode;

/* Structure for main nodes in the hash table */
typedef struct main_node
{
	/* Count of files */
    int filecount; 
	/* Word stored in the node */
    char word[50]; 
	/* Pointer to the next main node */
    struct main_node *mainnode_link; 
	/* Pointer to the sub-nodes */
    struct sub_node *subnode_link; 
} mnode;

/* Structure for the hash table */
typedef struct hash_table
{
	/* Hash key */
    int key; 
	/* Pointer to the main node associated with the key *//* Pointer to the main node associated with the key */
    struct main_node *link; 
} hash;


/*Function prototypes*/

int read_and_validate(int argc,char *argv[],Slist **head,Slist **tail);

int duplicate(Slist **head,char *filename);

int insert_at_last(Slist **head, char *data);

int create_node(Slist **new,char *data);

void print_list(Slist **head);

int createdb(hash *arr,int argc,char *argv[],Slist *head,mnode **main,snode **sub);

void create_HT(hash *HT);

int word_to_database(hash *HT,char *buff,Slist *head,mnode **main,snode **sub);

int createmnode(mnode **main,char *buff);

int createsnode(mnode **main,char *str);

void displaydb(hash *HT);

int searchdb(hash *HT);

int savedb(hash *HT);

int updatedb(hash *HT);

int file_to_database(char *arr,hash *HT);

int createmnode_upd(mnode **main,char *buff);

int createsnode_upd(mnode **main);

void print_subnodes(mnode *main);

int validate_file(char *str,hash *HT);

#endif