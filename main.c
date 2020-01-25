#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUM_LETTERS ((int)26)
#define END_CHAR 97
#define line_size 1024
#define word_size 12
#include "FuncTrie.h"


int main(int argc , char* argv[]) {

    node *root=getNode();
    int size=0;
    char *word=NULL;
    word =(char*)malloc(1*sizeof(char));
    if (word==NULL){
        printf("no allocet");
        exit(1);
    }
    char c;
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



