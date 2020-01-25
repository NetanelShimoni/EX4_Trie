typedef enum {FALSE=0 ,TRUE=1} boolean;
//build a node
typedef struct node{
    char letter;
    long unsigned int count;
    struct node* children [NUM_LETTERS];
} node;
node* getNode(void);
void printR(node *root, char *str, int index);
void insert(node **root,  char* key);
void print(node *root, char * str, int index);
void free_all(node* root);
int Stop(node *current);