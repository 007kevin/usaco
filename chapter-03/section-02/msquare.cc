/*
ID: min_j
LANG: C++
TASK: msquare
Date: 18/05/2015
Anaylsis:
  We could recursively attempt to solve this solution while memoizing 
  configurations to prune the recursive tree.
  
  ** Develop trie datastructure for memoizing permutations **
  Note: There are 8! = 40320 different permutations
*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#define SIZE 8
char init[SIZE+1] = "12348765";
char target[SIZE+1];
typedef struct node{ 
  char n;
  node *sib, *next;
} node;
node *HEAD;
node* insert(node *ptr, char *perm, int size){
  if (size == 0)
    return NULL;
  if (ptr == NULL){
    ptr = (node*) calloc(1,sizeof(node));
    ptr->sib=ptr->next=NULL;
    ptr->n = *perm;
  }
  node *cur = ptr;
  while (cur->sib != NULL && cur->n != *perm){
    cur = cur->sib;
  }
  if (cur->n == *perm)
    cur->next = insert(cur->next, perm+1, size-1);
  else
    cur->sib = insert(cur->sib, perm, size);
  return ptr;
}

int find(node *ptr, char *perm, int size){
  if (size == 0)
    return 1;
  node *cur = ptr;
  while(cur != NULL){
    if (cur->n == *perm){
      return find(cur->next,perm+1,size-1);
    }
    cur = cur->sib;
  }
  return 0;
}

void release_mem(node *ptr){
  if (ptr == NULL)
    return;
  release_mem(ptr->sib);
  release_mem(ptr->next);
  free(ptr);
}


  

int main(){
  FILE *fin = fopen("msquare.in","r");
  FILE *fout = fopen("msquare.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%c %c %c %c ",target,target+1,target+2,target+3);
  fscanf(fin,"%c %c %c %c ",target+7,target+6,target+5,target+4);
  target[SIZE] = '\0';
  fclose(fin);
  printf("%s\n",target);
  printf("%s\n",init);  
  HEAD = insert(HEAD,target,SIZE);
  HEAD = insert(HEAD,init,SIZE);
  printf("%d\n",find(HEAD,target,SIZE));
  printf("%d\n",find(HEAD,init,SIZE));

  
  release_mem(HEAD);
  fclose(fout);
  return 0;
}
  

