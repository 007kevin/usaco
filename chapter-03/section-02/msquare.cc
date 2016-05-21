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
#include <cstring>
#define SIZE 8
char init[SIZE+1] = "12348765";
char target[SIZE+1];
char sol[10000000];
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

void moveA(){
  char temp[SIZE/2];
  for (int i = 0; i < SIZE/2; ++i)
    temp[i] = init[i];
  for (int i = 0; i < SIZE/2; ++i)
    init[i] = init[i+SIZE/2];
  for (int i = 0; i < SIZE/2; ++i)
    init[i+SIZE/2] = temp[i];
}

void moveB(){
  char tmp = init[SIZE/2-1];
  for (int i = SIZE/2-1; i > 0; --i)
    init[i] = init[i-1];
  init[0] = tmp;
  tmp = init[SIZE-1];
  for (int i = SIZE-1; i > SIZE/2; --i)
    init[i] = init[i-1];
  init[SIZE/2] = tmp;
}

void moveC(){
  char tmp = init[1];
  init[1] = init[5];
  init[5] = init[6];
  init[6] = init[2];
  init[2] = tmp;
}

void print(char *ptr){
  for (int i = 0; i < SIZE/2; ++i)
    printf("%c",ptr[i]);
  printf("\n");
  for (int i = SIZE/2; i < SIZE; ++i)
    printf("%c",ptr[i]);
  printf("\n");
}

void solve(int I){
  if (strcmp(init,target) == 0){
    sol[I] = '\0';
    printf("solution: ");
    for (int i = 0; i < I; ++i)
      if (sol[i] == 'C')
        printf("(C)");
      else
        printf("%c",sol[i]);
    printf("\n\n");
    //    printf("solution: %s\n",sol);
    return;
  }
  if (find(HEAD,init,SIZE))
    return;
  HEAD = insert(HEAD,init,SIZE);

  sol[I] = 'A';
  moveA();
  solve(I+1);
  moveA();

  sol[I] = 'B';
  moveB();
  solve(I+1);
  moveB();
  moveB();
  moveB();
  
  sol[I] = 'C';
  moveC();
  solve(I+1);
  moveC();
  moveC();
  moveC();  
}

int main(){
  FILE *fin = fopen("msquare.in","r");
  FILE *fout = fopen("msquare.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%c %c %c %c ",target,target+1,target+2,target+3);
  fscanf(fin,"%c %c %c %c ",target+7,target+6,target+5,target+4);
  target[SIZE] = '\0';
  fclose(fin);

  solve(0);
  
  release_mem(HEAD);
  fclose(fout);        
  return 0;
}
