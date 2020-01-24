#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUM_LETTERS ((int)26)
#define END_CHAR 97
#define line_size 1024
#define word_size 12


typedef enum {FALSE=0 ,TRUE=1} boolean;

typedef struct node{
    char letter;
    long unsigned int count;
    struct node* children [NUM_LETTERS];
} node;

//char* check(char *key);


void printR(node *root, char *str, int index);



//init a new struct node
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
    int level;
    int length = strlen(key);
    int index;

   node *pCrawl = *root;

    for (level = 0; level < length; level++)
    {
        index = key[level]-'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
        pCrawl->letter=key[level];

    }

    // mark last node as leaf
    pCrawl->count++;
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
void free_all(node* root)
{
    int i;
    if(!root) return;   // safe guard including root node.

    // recursive case (go to end of trie)
    for (i = 0; i < NUM_LETTERS; i++)
        free_all(root->children[i]);


    // base case
    free(root);
}

int main(int argc , char* argv[]) {
//    printf("%s\n",argv[3] );
//    printf("%d\n",argc );
    node *root=getNode();
    char *extend_word=NULL;
    int size=0;
    char *word=NULL;
    word =(char*)malloc(1*sizeof(char));
    short sizeofword= sizeof(*word);
    char *index_for_free=word;
    if (word==NULL){
        printf("no allocet");
        exit(1);
    }
    char line[line_size];
    char c;
    int max_len=1;
    char *word_new=NULL;
    int len=0;
    boolean flag = FALSE;
    if(argc>=2 && strcmp(argv[1],"r")==0 ){
        flag=TRUE;
    }
    while ((c=getc(stdin))!=EOF){
        if (c >= 'A' && c <= 'Z' && c != '\t' && c != ' ' && c != '\n' && c != '\0') {
                char a = c + 32;
                c = a;
            }
        if (c >= 'a' && c <= 'z' && c != '\t' && c != ' ' && c != '\n' && c != '\0') {

            if (len == word_size){
                word_new=(char*)realloc(word, (size+word_size)* sizeof(char)); //+2 char
                len+=word_size;
                    if(word_new==NULL && word!=NULL){
                        free(word);
                        printf("not alocet");
                        exit(1);
                    }
                    word =(char*)calloc(len, sizeof(char));
                    strcpy(word,word_new);
                    free(word_new);
                    //max_len=len+2;
                }
            word[len]=c;
                len++;
        }
        if (c == '\t' || c == ' ' || c == '\n' || c == '\0'){
            word[len]='\0';
            insert(&root,word);
        len=0;
        }

    }
    if (flag){
        printR(root,word,0);
    }else{
        print(root,word,0);
    }
    free_all(root);
    free(word);

    return 0;
}




//    while (fgets(line, sizeof(line),stdin)) {
//        int counter = 0;
//        len = strlen(line);
//        for (int i = 0; i < len; i++) {
//            c = line[i];
//            if (c >= 'a' && c <= 'z' && c != '\t' && c != ' ' && c != '\n' && c != '\0') {
//                word[counter] = c;
//                counter++;
//            }
//            if (c >= 'A' && c <= 'Z' && c != '\t' && c != ' ' && c != '\n' && c != '\0') {
//                char a = c + 32;
//                c = a;
//                word[counter] = c;
//                counter++;
//            }
//
//            if (c == '\t' || c == ' ' || c == '\n' || c == '\0') {
//                word[counter] = '\0';
//                boolean flag = FALSE;
//                for (int j = 0; j < strlen(word); j++) {
//                    if (word[j] ==' ') {
//                        flag = TRUE;
//                    }
//                }
//                if (flag == FALSE) {
//                    insert(root, word);
//                    counter = 0;
//                }
//            }
//        }
//    }
//
//char str[word_size];
//    if (flag){
//        printR(root,str,0);
//    }else{
//        print(root,str,0);
//    }
//    free_all(root);

