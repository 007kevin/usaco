/*
  Cow Pedigrees
  
  Analysis:
  This is a DP problem. The properties of a tree that we are interested in are depth and number of nodes,
  so we'll make a table: table[i][j] contains the number of trees with depth i and number of nodes j. 
  Given the constraints of the task, j must be odd. How do you construct a tree? 
  From smaller trees, of course. A tree of depth i and j nodes will be constructed from 
  two smaller trees and one more node.

  With i and j already chosen, we chose k, which is the number of nodes in the left subtree. 
  Then the number of nodes in the right subtree is known, j-k-1. For depth, at least 
  one subtree has to have depth i-1 so that the new made tree would have depth i. There are 
  three possibilities: the left subtree can have depth i-1 and the depth of the 
  right subtree can be smaller, the right subtree can have depth i-1 and the depth 
  of the left subtree can be smaller, or they can both have depth i-1.

  The truth is that once we are constructing trees of depth i, we use smaller trees, 
  but we only care if those are of depth i-1 or smaller. So, let another array, 
  smalltrees[i-2][j] contain number of trees of any depth smaller than i-1, 
  not just i-2. Now, knowing all this, we contruct our tree from three possible ways:

  table[i][j] += smalltrees[i-2][k]*table[i-1][j-1-k];
  // left subtree smaller than i-1, right is i-1
  table[i][j] += table[i-1][k]*smalltrees[i-2][j-1-k];
  // left subtree is i-1, right smaller
  table[i][j] += table[i-1][k]*table[i-1][j-1-k];
  // both i-1 
  In addition, if the number of nodes in the left subtree is smaller then 
  the number of nodes in the left subtree, we can count the tree twice, as 
  different tree can be constructed by swapping left and right subtree.

  Total running time is O(K*N^2),with very favorable constant factor.
*/
#include <cstdio>
#include <cstdlib>
#include <cassert>
#define MOD 9901
using namespace std;

int table[101][202],N,K,c;
int smalltrees[101][202];

FILE *fin=fopen("nocows.in","r");
FILE *fout=fopen("nocows.out","w");

int main() {
  fscanf (fin,"%d %d",&N,&K);
  table[1][1]=1;
  for (int i=2;i<=K;i++) {
    for (int j=1;j<=N;j+=2)
      for (int k=1;k<=j-1-k;k+=2) {
        if (k!=j-1-k) c=2; else c=1;    
        table[i][j]+=c*(
                        smalltrees[i-2][k]*table[i-1][j-1-k]  // left subtree smaller than i-1
                        +table[i-1][k]*smalltrees[i-2][j-1-k]  // right smaller
                        +table[i-1][k]*table[i-1][j-1-k]  // both i-1
                        );
        table[i][j]%=MOD;
      }
    for (int k=0;k<=N;k++) {          // we ensure that smalltrees[i-2][j] in the next i
      smalltrees[i-1][k]+=table[i-1][k]+smalltrees[i-2][k]; // iteration contains the number
      smalltrees[i-1][k]%=MOD;           // of trees smaller than i-1 and with j nodes
    }
  }

  for (int k = 1; k <= K; ++k){
    for (int n = 1; n <= N; ++n)
      printf("%d ", table[k][n]);
    printf("\n");
  }
  printf("----\n");
  for (int k = 1; k <= K; ++k){
    for (int n = 1; n <= N; ++n)
      printf("%d ", smalltrees[k][n]);
    printf("\n");
  }

    
  fprintf (fout,"%d\n",table[K][N]);
  return 0;
}
