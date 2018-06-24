#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
void linit(list *l){
  l->head = NULL;
  l->tail = NULL;
}
/* finds coloumn according to which sortinig is to be done */
char *getcoloumn(char *str, int is_k) {
  char *r;
  r = (char*)malloc(strlen(str) * sizeof(char));
  strcpy(r, str);
  char *re;
 if(is_k == 1) {
    return str;
  }
  int cnt = 0, j = 0;
  while(str[j] != '\0') {
    if((str[j] == ' ') || (str[j] == '\t')){
      cnt++;
    }
    j++;
  }
  if((is_k - 1) > cnt) {
    re = (char*)malloc(sizeof(char) * (2));
    strcpy(re, " ");
    return re;
  }
  int i;
  re = strtok(r, " \t\n");
  for( i = 0; i < (is_k - 1); i++) {
    
    re = strtok(NULL, " \t\n");
  }
  //printf(" %s \n", re);
  return re;
}
/* creates list of sentences and stores it for sorting purpose */
void enl(list *l, char *str, int is_k, int is_i) {
  node *tmp/*, *tr */;
  tmp = (node*)malloc(sizeof(node));
  tmp->next = NULL;
  tmp->prev = NULL;
  tmp->orig = str;
  tmp->new = makesmall(str, is_i);
   if(is_k) {
     tmp->korig = getcoloumn(str, is_k);
     tmp->knew = makesmall(tmp->korig, is_i);
     // printf(" %s\n", tmp->knew);
   } else {
     tmp->korig = NULL;
     tmp->knew = NULL;
   }
   /*need makesmall function returning char pointer, pointing to string containing all small laters of orig string
     char *makesmall(char *str) created in functions*/
   if(l->head == NULL) {
     l->head = tmp;
     l->tail = tmp;
     return;
   }
   l->tail->next = tmp;
   tmp->prev = l->tail;
   l->tail = l->tail->next;
   return;
   
}
/* adds node add in a list before address of given pointer p */
void addbefore(node *p, node *add, list *l){
  if(p->prev == NULL) {
    p->prev = add;
    add->next = p;
    add->prev = NULL;
    l->head = add;
    return;
  }
  add->prev = p->prev;
  add->next = p;
  p->prev->next = add;
  p->prev = add;
  }
/* adds node add in a list after address of given pointer p */
void addafter(node *p, node *add, list *l) {
  if(p->next == NULL) {
    p->next = add;
    add->prev = p;
    add->next = NULL;
    l->tail = l->tail->next;
    return;
  }
  //if(p->next == NULL){
  add->prev = p;
  add->next = p->next;
  p->next = add;
  add->next->prev = add;
  return;
}
/* prints original strings in a list */
void printl(list *l) {
  node *tr;
  if(l->head == NULL) {
    //printf("nothing is in list\n");
    return;
  }
  tr = l->head;
  while(tr != NULL) {
    printf("%s\n", tr->orig);
    tr = tr->next;
  }
  return;
}
/* reverses the list by swapping head and tail, and next and prev pointers*/
void reverse(list *l) {
  node *hold_h = l->head;
  node *hold_t = l->tail;
  node *tmp = NULL;  
  node *cur = l->head;
     
  while (cur !=  NULL) {
    tmp = cur->prev;
    cur->prev = cur->next;
    cur->next = tmp;              
    cur = cur->prev;
  }      
     
  if(tmp != NULL ){
    l->head = hold_t;
    l->tail = hold_h;
  }
}



/* removes node of given address q */

node *rmnode(node *q, list *l) {
  if((q == l->head) && (q == l->tail)){
    l->head = NULL;
    l->tail = NULL;
    return q;
  }
  if(q == l->head) {
    l->head = l->head->next;
    l->head->prev = NULL;
    q->next = NULL;
    return q;
  }
  if(q == l->tail) {
    l->tail = l->tail->prev;
    l->tail->next = NULL;
    q->prev = NULL;
    return q;
  }
  node *tmp;
  tmp = l->head;
  while(tmp != q->prev)
    tmp = tmp->next;
  tmp->next = q->next;
  q->next->prev = tmp;
  return q;
}


/* compares new and knew element(string) in the node */
int cmpnew(node *p, node *q, int is_k) {
  int n;
  if(is_k){
    n = strcmp(p->knew, q->knew);
    return n;
  }
  n = strcmp(p->new, q->new);
  return n;
}
/* compares orig and korig element(string) in the node */
int cmporig(node *p, node *q, int is_k, int is_b) {
  int n;
  if(is_k){
    n = strcmp(p->korig, q->korig);
    return n;
  }
  char *strp, *strq;
  strp = (char*)malloc(sizeof(char) * strlen(p->orig));
  strcpy(strp, p->orig);
  strq = (char*)malloc(sizeof(char) * strlen(q->orig));
  strcpy(strp, q->orig);
  if(is_b){
    int i = 0;
    while((*(strp) == ' ') || (*(strp) == '\t')) {
      //i++;
      (strp)++;
      }
    while((*(strq) == ' ') || (*(strq) == '\t')) {
      //i++;
      (strq)++;
      }
  }
    n = strcmp(strp, strq);
    return n;
}


/* This function converts any string into small lettered string */
char* makesmall(char *s, int is_i) {
  int i = 0, j = 0, c = 0;
  char *p, *ns;
  ns = (char*)malloc(sizeof(char) * strlen(s));
  while((s[j] == ' ') || (s[j] == '\t')){
    j++;
  }
  while(s[j] != '\0'){
    ns[c] = s[j];
    c++;
    j++;
  }
  ns[c] = '\0';
  p = (char*)malloc(strlen(s) * sizeof(char));
  while(ns[i] != '\0') {
    if(ns[i] <= 'Z'  && ns[i] >= 'A'){
      p[i] = ns[i] + 32;
      //      printf("%c", p[i]);
    }
    else{
      p[i] = ns[i];
    }
    i++;
  }
  p[i] = ns[i];
  //printf("\n");
  return p;
}



/* this function sorts string accordint to given attributes */

int sort_1(list *l, int is_k, int is_r, int is_b, int is_n) {
  if(l->head == NULL) {
    return -1;
  }
  node *min, *hold, *add, *tr, *pos, *tmp;
  int i, x, y, m, n;
  pos = l->head;
  while(pos->next != NULL) {
    tr = pos->next;
    min = pos;
    while(tr != NULL) {
      if(!is_n){
	x = cmpnew(min, tr, is_k);
	if(x > 0)
	  min = tr;
	if(x == 0) {
	  y = cmporig(min, tr, is_k, is_b);
	  if(y < 0) {
	    min = tr;
	  }
	  if(y == 0) {
	    if(is_k) {
	      n = cmpnew(min, tr, 0);
	      if(n > 0){
		min = tr;
	      }
	      if(n == 0) {
		m = cmporig(min, tr, 0, is_b);
		if(m < 0) {
		  min = tr;
		}
		if(m == 0) {
		  min = tr;
		}
	      }
	    }else{
	      min = tr;
	    }
	  }
	}
      }else{//sorting based on numcmp is written need to check again
	x = numcmp(min, tr, 0, is_k);
	if(x > 0) {
	  min = tr;
	}
	if(x == 0){
	  min = tr;
	}
	if(x == 2) {
	  y = strcmp(min->new, tr->new);
	  if(y > 0) {
	    min = tr;
	  }
	  if(y == 0){
	    m = strcmp(min->orig, tr->orig);
	    if(m < 0){
	      min = tr;
	    }
	  }
	}
      }
	/*if(x < 0) {
	  min = min;
	  }*/
      tr = tr->next;
    }
    if(min == pos){
      pos = pos->next;
    }
    else{
      hold = rmnode(min, l);
      addbefore(pos, hold, l);
    }
  }
  if(is_r) {
    reverse(l);
  }
  return 1;
}



/* this function removes duplicate elements in the given list  */
void remdp(list *l, int is_b){
  if(l->head == NULL || l->head->next == NULL) {
    return;
  }
  int m;
  node *p1, *p2;
  for(p1 = l->head; p1 != NULL; p1 = p1->next) {
    p2 = p1->next;
    while(p2 != NULL) {
      if(is_b == 0)
	m = strcmp(p1->orig, p2->orig);
      else{
	char *s1, *s2;
	s1 = (char*)malloc(strlen(p1->orig));
	s2 = (char*)malloc(strlen(p2->orig));
	
	strcpy(s2, p2->orig);
	strcpy(s1, p1->orig);
	while(*s2 == '\t' || *s2 == ' ')
	  *s2++;
	while(*s1 == '\t' || *s1 == ' ')
	  *s1++;
	m = strcmp(s1, s2);
      }
      if(m == 0){
	node *next = p2->next;
	  rmnode(p2, l);
	p2 = next;
      }
      else{
	p2 = p2->next;
      }
    }
  }
}



/* this function compares strings in the given two nodes according to */
/* given attributes */
/*cfg nahi kadhal*/
#define M 1024
int numcmp(node *p, node *q, int nissame, int is_k) {
  int t1, t2, la, lb, tmp, tmp1, lpin, lqin, i, j, f1 = 0, f2 = 0, ff1 = 0, ff2 = 0, re1, r, m, z1, z2, lz1, lz2, z1f = 0, z2f = 0, spcnt = 0, sqcnt = 0, pneg = 0, qneg = 0;
  char *pdc, *qdc, *pin, *qin, *pnum, *qnum, pn[M], qn[M], *pcm, *qcm;
  pnum = (char*)malloc(sizeof(char) * strlen(p->orig));
  qnum = (char*)malloc(sizeof(char) * strlen(q->orig));
  if(nissame) {
    if(is_k){
      strcpy(pnum, p->korig);
      strcpy(qnum, q->korig);
    } else {
      strcpy(pnum, p->orig);
      strcpy(qnum, q->orig);
    }
  }
  else {
    if(is_k){
      strcpy(pnum, p->knew);
      strcpy(qnum, q->knew);
    } else {
      strcpy(pnum, p->new);
      strcpy(qnum, q->new);
    }
  }
  z1 = 0;
  spcnt = 0;
  while(((pnum[z1] == ' ') || (pnum[z1] == '\t') || (pnum[z1] == '\n')) && (pnum[z1] != '\0')) {
    spcnt++;
    z1++;
  }
  lz1 = strlen(pnum);
  z2 = 0;
  sqcnt = 0;
  while(((qnum[z2] == ' ') || (qnum[z2] == '\t') || (pnum[z2] == '\n')) && (qnum[z2] != '\0')) {
    sqcnt++;
    z2++;
  }
  lz2 = strlen(qnum);
  if(spcnt == lz1){
    z1f = 1;
  }
    //return -1;
  if(sqcnt == lz2){
    z2f = 1;
    }
    //return 1;
  if(z1f && z2f)
    return 0;
  if(z1f && !z2f)
    return -1;
  if(!z1f && z2f)
    return 1;
  while((*pnum == ' ') || (*pnum == '\t')) {
    *p++;
  }
  // printf("%s \n", pnum);
  
  while((*qnum == ' ') || (*qnum == '\t')) {
    *qnum++;
  }
  //printf("%s \n", qnum);
  
  if(*pnum == '-'){
    pneg = 1;
    *pnum++;
  }
  //printf("%s \n", pnum);
  if(*qnum == '-'){
    qneg = 1;
    *qnum++;
  }
  //printf("%s \n", qnum);
  
  if(((pnum[0] > '9') || (pnum[0] < '0')) && !(pnum[0] == ' ') && !(pnum[0] == '-')) {
    pin = (char*)malloc(sizeof(char) * 2);
    f1 = 1;//f1 remebers if number started with nonnumeric char
    pin = "0";
  }
  if(((qnum[0] > '9') || (qnum[0] < '0')) && !(qnum[0] == ' ') && !(qnum[0] == '-')) {
    qin = (char*)malloc(sizeof(char) + 1);
    qin = "0";
    f2 = 1;
  }
  if(((pnum[0] <= '9') && (pnum[0] >= '0'))/* || (pnum[0] == '-')*/) {
    while(*pnum == '0') {
      pnum++;
      if(*pnum == '.') {
	pin = (char*)malloc(sizeof(char) * 2);
	pin = "0";
	break;
      }
    }
    i = 0;
    while((pnum[i] != '.') && (pnum[i] != '\0')) {
      if((pnum[i] > '9') || (pnum[i] < '0')) {
	pcm = &pnum[i];
	ff1 = 1;//ff1 & ff2 indicates existance of alphabets after numbers
	break;
      }
      pn[i] = pnum[i];
      i++;
    }
    pn[i] = '\0';
    pin = (char*)malloc(sizeof(char) * strlen(pn));
    strcpy(pin, pn);
    lpin = strlen(pin);
    int j = i;
    while(pnum[i] != '\0') {
      if(!ff1){
	if((pnum[i] > '9') || (pnum[i] < '0')) {
	  pcm = &pnum[i];
	  ff1 = 1;
	  break;
	}
      }
      pn[i - j] = pnum[i];
      i++;
    }
    pn[i -j] = '\0';
    pdc = (char*)malloc(sizeof(char) * strlen(pn));
    strcpy(pdc, pn);
  }
  if(qnum[0] <= '9' && qnum[0] >= '0') {
    while(*qnum == '0') {
      qnum++;
      if(*qnum == '.') {
	qin = "0";
	break;
      }
    }
    // printf("%s is pnum\n", pnum);
    i = 0;
    while((qnum[i] != '.') && (qnum[i] != '\0')) {
      if((qnum[i] > '9') || (qnum[i] < '0')) {
	qcm = &qnum[i];
	ff2 = 1;//remebers if after some numbers char string starts
	break;
       }
     qn[i] = qnum[i];
      i++;
    }
    qn[i] = '\0';
    // printf("%s is qnum\n", qnum);
    qin = (char*)malloc(sizeof(char) * strlen(qn));
    strcpy(qin, qn);
    lqin = strlen(qin);
    j = i;
    while(qnum[i] != '\0') {
      if(!ff2) {
	if((qnum[i] > '9') || (qnum[i] < '0')) {
	  qcm = &qnum[i];
	  ff2 = 1;
	  break;
	}
      }
      qn[i - j] = qnum[i];
      i++;
    }
    qn[i -j] = '\0';
    qdc = (char*)malloc(sizeof(char) * strlen(qn));
    strcpy(qdc, qn);
  }
  if(f1 && f2) {
    t1 = strcmp(p->new, q->new);
    if(t1 > 0) {
      return 1;
    }
    if(t1 < 0) {
      return -1;
    }
    if(t1 == 0) {
      t2 = strcmp(p->orig, q->new);
      if(t2 > 0)
	return -1;
      if(t2 < 0)
	return 1;
      if(t2 == 0)
	return 0;
    }
  }
  if(pneg && !qneg) {
    return -1;
  }
  if(!pneg && qneg) {
    return 1;
  }
  // if(pneg && qneg){
  //}
  if(lpin > lqin) {
    if(pneg && qneg){
      return -1;
    }
     return 1;// 1 indicates first no is greater than second
  }
  if(lpin < lqin) {
    if(pneg && qneg){
      return 1;
    }
    return -1;//-1 indicates first no is less than second
  }
  if(lpin == lqin) {//d
  
    tmp = strcmp(pin, qin);
    if(tmp > 0){
      if(pneg && qneg){
	return -1;
      }
      return 1;
    }
    if(tmp < 0) {
      if(pneg && qneg){
	return 1;
      }
      return -1;
    }
    if(tmp == 0) {
      tmp1 = strcmp(pdc, qdc);
      if(tmp1 > 0){
	if(pneg && qneg){
	  return -1;
	}
	return 1;
      }
      if (tmp1 < 0) {
	if(pneg && qneg){
	  return 1;
	}
	return -1;
      }
      if(tmp1 == 0)
	if(ff1 || ff2) {
	  int eu = strcmp(pcm, qcm);//pcm and qcm are the strings of alphabets after numbers
	  if(eu > 0){
	    if(nissame) {
	      return -1;
	    }
	    return 1;
	  }
	  if(eu < 0){
	    if(nissame) {
	      return 1;
	    }
	    return -1;
	  }
	  if(eu == 0){
	    if(nissame) {
	      //if(is_k) {//
	      //}//
	      return 0;
	    }
	    if(is_k) {//
	      //      return numcmp(p, q, 0, 0);
	      r = strcmp(p->new, q->new);
	      if(r > 0){
		return 1;
	      }
	      if(r < 0){
	      return -1;
	      }
	      if(r == 0){
		//return 0;
		m = strcmp(p->orig, q->orig);
		if(m > 0){
		   return -1;
		}
		if(m < 0){
		  return 1;
		}
		if(m == 0){
		  return 0; //numcmp(p, q, 1, 0);
		}
	      }
	      
	    }//
	    re1 = numcmp(p, q, 1, is_k);
	    return re1;
	  }
	}
      if(is_k) {//
	//      return numcmp(p, q, 0, 0);
	r = strcmp(p->new, q->new);
	if(r > 0){
	  return 1;
	      }
	if(r < 0){
	  return -1;
	}
	if(r == 0){
	  //return 0;
	  m = strcmp(p->orig, q->orig);
	  if(m > 0){
	    return -1;
	  }
	  if(m < 0){
	    return 1;
	  }
	  if(m == 0){
	    return 0; //numcmp(p, q, 1, 0);
	  }
	}
      }
      return 0;
    }
  }
}
