/*  This is the node I've used for storing data. */
/* In this orig sortes the original read string, new store the string containing */
/* only small letters, and knew and korig does same thing for kts coloun element */
typedef struct node{
  char *orig, *new, *korig, *knew;
  struct node *next, *prev;
}node;
/*this is list defination*/
typedef struct list{
  node *head, *tail;
}list;
/*here we have declaration of all functions in the list.h*/
void linit(list *l);
char *makesmall(char *str, int is_i);
int sort_1(list *l, int is_k, int is_r, int is_b, int is_n);
int numcmp(node *p, node *q, int oissame, int is_k);
void remdp(list *l, int is_b);
void enl(list *l, char *s, int is_k, int is_i);
void addbefore(node *p, node *add, list *l);
void addafter(node *p, node *add, list *l);
void printl(list *l);
void rprintl(list *l);
void swap(node *p, node *q, list *l);
node *rmnode(node *q, list *l);
