#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUM_LETTERS ((int)26)
#define END_CHAR 97
#define line_size 1024
#define word_size 12

#include "FuncTrie.h"

void printR(node *root, char *str, int index);
/// new struct node
node* getNode(void)
{
    node *root = NULL;
    root = (node *)malloc(sizeof(node));
    if (root)
    {
        int i;

        root->count = 0;

        for (i = 0; i < NUM_LETTERS; i++)
            root->children[i] = NULL;
    }

    return root;
}
//add a word to the trie
void insert(node **root,  char* key)
{
    int i;
    int length = strlen(key);
    int index;
    node *runner = *root;
    for (i = 0; i < length; i++)
    {
        index = key[i]-'a';
        if (!runner->children[index])
            runner->children[index] = getNode();
        runner = runner->children[index];
        runner->letter=key[i];

    }
    // mark last node as leaf
    runner->count++;
}

//function that check if the node have at least one children
int Stop(node *current){
    boolean flag=FALSE;
    for (size_t i = 0; i < NUM_LETTERS; i++)
    {
        if(current->children[i])
            flag=TRUE;
    }
    return flag;
}

//print the words in trie sorted by a rising lexicographic order
void printR(node *root, char *str, int index)
{

    for (int i = NUM_LETTERS - 1; i >= 0; i--)
    {
        if (root->children[i])
        {
            str[index] = root->children[i]->letter;
            printR(root->children[i], str, index + 1);
        }
    }

    if (Stop(root) == FALSE)
    {
        str[index] = '\0';
        printf("%s\t%ld\n", str, root->count);
        return;
    }

    if (root->count > 0 )
    {
        str[index] = '\0';
        printf("%s\t%ld\n", str, root->count);
    }

}

///print the words in trie sorted by a declining lexicographic order
void print(node *root, char * str, int index) {
    if(Stop(root)==FALSE)
    {
        str[index]='\0';
        printf("%s\t%ld\n",str,root->count);
        return;
    }
    if (root->count>0){
        str[index]='\0';
        printf("%s\t%ld\n" , str,root->count);
    }
    for (size_t i = 0; i <NUM_LETTERS; i++)
    {
        if(root->children[i]){
            str[index]=root->children[i]->letter;
            print(root->children[i],str,index+1);
        }
    }
}
//free the memory of all the nodes in the root
void free_all(node* root) {
    int i;
    if (!root) return;   // safe guard including root node.

    // recursive case (go to end of trie)
    for (i = 0; i < NUM_LETTERS; i++)
        free_all(root->children[i]);


    // base case
    free(root);
}




