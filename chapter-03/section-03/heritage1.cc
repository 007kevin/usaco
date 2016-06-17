/*
ID: min_j
LANG: C++
TASK: heritage
Date: 15/06/2016
Anaylsis:
  Break up inorder into substrings of occuring 
  nodes of matching preorder nodes to rebuild
  the tree

  I like this solution:

  India's Nishant Redkar
  #include <fstream>
  #include <string>
  using namespace std;
  
  ofstream out ("heritage.out");
  
  void
  recursex (string sin, string spre) {
      int i;
      if (sin.length() < 2) {
        	out << sin;
  	        return;
      }
      for (i = 0; sin[i] != spre[0]; i++);
      recursex (sin.substr(0,i), spre.substr(1,i));
      recursex (sin.substr(i+1), spre.substr(i+1));
      out << spre[0];
  }
  
  int
  main () {
      string sin, spre;
      ifstream in("heritage.in");
      in >> sin >> spre;
      recursex (sin, spre);
      out << endl;
      in.close();
      out.close();
      return 0;
  }
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#define MAXN 27
char  inorder[MAXN];
char preorder[MAXN];
typedef struct node {
  char v;
  node *left, *right;
} node;
node *head;
node* buildTree(int s, int e){
  if (s == e) return NULL;
  int i,j;
  for (i = 0; i < strlen(preorder); ++i){
    for (j = s; j < e; ++j)
      if (preorder[i] == inorder[j])
        break;
    if (j != e) break;
  }
  node *n = (node*) malloc(sizeof(node));
  assert(n!=NULL);
  n->v = inorder[j];
  n->left = buildTree(s,j);
  n->right = buildTree(j+1,e);
  return n;
}

void print(FILE *fout, node *n){
  if (n == NULL) return;
  print(fout, n->left);
  print(fout, n->right);
  fprintf(fout,"%c",n->v);
}

void destruct(node *n){
  if (n == NULL) return;
  destruct(n->left);
  destruct(n->right);
  free(n);
}


int main(){
  FILE *fin = fopen("heritage.in", "r");
  FILE *fout = fopen("heritage.out", "w");
  assert(fin!=NULL);
  assert(fout!=NULL);
  fscanf(fin,"%s",inorder);
  fscanf(fin,"%s",preorder);
  fclose(fin);
  head = buildTree(0,strlen(inorder));
  print(fout,head);
  fprintf(fout,"\n");
  destruct(head);
  fclose(fout);
  return 0;
}

