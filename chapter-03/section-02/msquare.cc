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
char init[SIZE] = {1,2,3,4,8,7,6,5};
char target[SIZE];
typedef struct node{ 
  char n;
  node *sib, *next;
} node;
node *HEAD;
void insert(node *ptr, char *perm, int size){
  if (size == 0)
    return;
  if (ptr == NULL){ // initialize HEAD
    ptr = (node*) calloc(1,sizeof(node));
    ptr->sib=ptr->next=NULL;
  }
  node *cur = ptr;
  while(cur->sib != NULL || cur->n != *perm)
    cur = cur->sib;
  
}


  

int main(){
  FILE *fin = fopen("msquare.in","r");
  FILE *fout = fopen("msquare.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%d%d%d%d",target,target+1,target+2,target+3);
  fscanf(fin,"%d%d%d%d",target+7,target+6,target+5,target+4);
  fclose(fin);

  fclose(fout);
  return 0;
}
  

