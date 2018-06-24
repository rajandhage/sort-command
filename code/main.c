#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<ctype.h>
#include"list.h"
int readfile(char *name, list *l, int is_k, int is_i);
int getdata(list *l, int is_k, int is_n, int is_i);
char *readstring();
/* this function is to get the data from user if not any file for sorting is given */
int getdata(list *l, int is_k, int is_n, int is_i) {
  char *s;
  int i = 0;
  while((s = readstring()) != NULL){
    enl(l, s, is_k , is_i);
  }
}
/*this function is supplimentry function for getdata function. It is used to get lines from terminal by user*/
char *readstring(){
  char ch, s[10000], *c;
  int i = 0;
  while((ch = getchar()) != '\n'){
    if(ch == EOF){
      return NULL;
    }
    s[i++] = ch;
  }
  s[i] = '\0';
  c = (char*)malloc(strlen(s) * sizeof(char));
  strcpy(c, s);
  return c;
}
/*this is structure to store the given attributes*/
typedef struct getcommand{
  int is_k;
  int is_n;
  int is_i;
  int is_m;
  int is_d;
  int is_b;
  int is_t;
  int is_r;
  int is_u;
  char ar_t;
  //int gs;
}storekey;
/*this function initializes all value in storekey to 0*/
void initkey(storekey *k) {
  k->is_k = 0;
  k->is_n = 0;
  k->is_i = 0;
  k->is_m = 0;
  k->is_d = 0;
  k->is_b = 0;
  k->is_t = 0;
  k->is_r = 0;
  k->is_u = 0;
}
/*And this is our main function where our all functions get used*/
int main(int argc, char *argv[]) {
  int i, j, s, x, fflag = 0;
  list l;
  linit(&l);
  storekey *k = (storekey*)malloc(sizeof(storekey));
  initkey(k);
  char ch   /*stores k*/;
  int fd, flno = 0;
  char **fn = (char**)malloc(argc * sizeof(char*));
    for(i = 1; i < argc; i++) {
      if(argv[i][0] == '-') {
	switch(argv[i][1]) {
	case 'r':
	  k->is_r = 1;
	  break;
	  case 'k':
	  if(strlen(argv[i]) > 2) {
	    j = 2;
	    s = 0; 
	    while((ch = argv[i][j])) {
	      if(isdigit(argv[i][j])){
		s = s * 10 + argv[i][j] - '0';
		j++;
	      }
	      else {
		printf("Give appropriate coloumn number\n");
		return 1;
	      }
	    }
	    k->is_k = s;
	  }
	  else {
	    j = 0; s = 0; i++;
	    if(i == argc) {
	      printf("Sort: Option requires an argument --'k'\n\n");
	      return 1;
	    }
	    while((ch = argv[i][j]))
	      if(isdigit(argv[i][j])){
		s = s * 10 + argv[i][j++] - '0';
	      }
	      else {
		printf("Invalid number at field start: Invalid count at start of '%c'\n", ch);							
		return 1;
	      }
	    k->is_k = s;
	  }						
	    break;
	case 'u':
	  k->is_u = 1;
	  break;
	case 't':
	  k->is_t = 1;
	  if(strlen(argv[i]) > 2) {
	    j = 2;
	    s = 0; 
	  k->ar_t = argv[i][j];
	  }
	  else {
	    j = 0; s = 0; i++;
	    if(strlen(argv[i]) > 1){
	      printf("Delimeter of more than one character is not allowed\n");
	      return 1;
	    }
	    if(i == argc) {
	      printf("Required arguments for -t is  not given\n");
	      return 1;
	    }
	    k->ar_t = argv[i][j];
	  }
	  break;

	case 'n':
	  k->is_n = 1;
	  break;
	case 'm' :
	  k->is_m = 1;
	  break;
	case 'i':
	  k->is_i = 1;
	  break;
	case 'b' :
	  k->is_b = 1;
	  break;
	default:
	  printf("You have given invalid attribute'%s'\n", argv[i]);
	  return 1;
	}
      }
      else {
	fd = open(argv[i], O_RDONLY);
	if(fd != -1) {
	  fn[flno] = argv[i];
	  (flno)++;
	  fflag++;
	  close(fd);
	}else{
	  if(fd == -1){
	    fflag == 0;
	    printf("Error in opening the file or file does not exists %s\n", argv[i]);
	    return 1;
	  }
	}
      }
    }
    if(fflag){
    i = 0;
    for(i = 0; i < flno; i++) {
      readfile(fn[i], &l, k->is_k, k->is_i);
    }
  } else {
    getdata(&l, k->is_k, k->is_n, k->is_i);
  }
    if(k->is_m){
      printl(&l);
      return 1;
    }
    sort_1(&l, k->is_k, k->is_r, k->is_b, k->is_n);
  if(k->is_u) {
    remdp(&l, k->is_b);
  }
  printl(&l);
  return 1;
}
 /* to decide limit of no of chars in line change m */
 /* This function reads the file given by user and stores data read in the list */
#define M 1024
int readfile(char *name, list *l, int is_k, int is_i) {
  int fd, i = 0;
  char *s, ch, arr[M];
  fd = open(name, O_RDONLY);
  while(read(fd, &ch, sizeof(char))) {
    if(ch == '\n'){
	arr[i] = '\0';
	s = (char*)malloc(strlen(arr) * sizeof(char));
	strcpy(s, arr);
	enl(l, s , is_k, is_i);
	i = 0;
    }
    else{
	arr[i] = ch;
	i++;
    }
  }
  close(fd);
}
