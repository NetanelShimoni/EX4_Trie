#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUM_LETTERS ((int)26)
#define END_CHAR 97

typedef enum {FALSE=0 ,TRUE=1} boolean;

typedef struct node{
    char letter;
    long unsigned int count;
    struct node* children [NUM_LETTERS];
} node;
void lowerstring(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        str[i]=tolower(str[i]);
    }

}

node* newnode(char a){
    node *p=NULL;
    p=(node*)malloc(sizeof(node));
    if(p==NULL){
        printf("malloc is not working\n");
    }else {
        p->letter=a;
        for (int i = 0; i < NUM_LETTERS; ++i) {
            p->children[i]=(node*) malloc(sizeof(node));
            if(p==NULL){
                printf("malloc not sucssed to children\n");
            }
        }
        p->count = 0;
    }
    return p;
}
void insert (node** root,char* a){
    boolean inserted=FALSE;
    printf("sddsd");
    int j=0,i=0;
    ///make lower char
  //  lowerstring(a);

    int sizestring = strlen(a);
    if(*root!=NULL){
    for (; i < sizestring; i++) {
        int value =a[i];
    for ( ; j <NUM_LETTERS ; j++) {
        if(a[i]==(*root)->children[j]->letter){
            root=&((*root)->children[j]);
            if ((*root)==NULL){
                *root=newnode(a[i]);
            }
            inserted=TRUE;
            ////break becuse we not need to chack all array and same place
            break;
        }}
    ////not fount the letter and not inserted
    if (!inserted){
            //(*root)->children[value-END_CHAR]->letter=a[i];
            *root=newnode(a[i]);
            i++;
           // root=&((*root)->children[value-END_CHAR]);
            for (int k = i; k <sizestring; k++) {
                if (k!=sizestring-1) {
                    int value = a[k];
                    int updatvalue = a[k + 1];
                    *root = newnode(a[k]);
                    (*root)->children[updatvalue - END_CHAR]->letter = a[k + 1];
                    root = &((*root)->children[updatvalue - END_CHAR]);
                }else{
                    int value = a[k];
                    *root = newnode(a[k]);
                    (*root)->count++;
                }
            }
//                *root=newnode(a[k]);
//                value=a[k];
//                (*root)->children[value-END_CHAR]->letter=a[k+1];
//                root=&((*root)->children[value-END_CHAR]);
//            }
            return;
        }

    }
}
    for (int l = 0; l <sizestring; l++) {
        if (l!=sizestring-1) {
            int value = a[l];
            int updatvalue = a[l + 1];
            *root = newnode(a[l]);
            (*root)->children[updatvalue - END_CHAR]->letter = a[l + 1];
            root = &((*root)->children[updatvalue - END_CHAR]);
        }else{
            int value = a[l];
            *root = newnode(a[l]);
            (*root)->count++;
        }
    }
}
void printTrie(node **root, char str[],int level){
    if(*root==NULL){
        return;
    }
        for (int i = 0; i <NUM_LETTERS ; ++i) {
            if((*root)->children[i]){
                str[level]= i +'a';
                printTrie((*root)->children[i],str,level+1);
            }
    }
}
void free_all(node** root)
{
    int i;
    if(!*root) return;   // safe guard including root node.

    // recursive case (go to end of trie)
    for (i = 0; i < NUM_LETTERS; i++)
        free_all((*root)->children[i]);


    // base case
    free(*root);
}




int main() {
    node** root =NULL;
    insert(&root,"aba");
    insert(&root,"mn");
    insert(&root,"kfhf");
    insert(&root,"duehfd");
    insert(&root,"djfj");
    int level =0;
    char str[20];
    printf("dfdf");
    printTrie(root,str,level);
    free_all(root);
    return 0;
}