/*
ID: min_j
LANG: C++
TASK: kimbits
Date: 15/05/2015
Anaylsis:
  setsize(N,L) = setsize(N-1,L) + setsize(N-1,L-1)
  Given a bitstring, the I'th number will have its msp bit either 0 or 1.
  We will know this by comparing setsize(N-1,L) >= I. If true, then we know I'th
  element is within that set size and msb is '0'. Else I'th element is not within
  that set therefore msb must be '1'. Continue with this recurrence relation to
  build the I'th bitstring.
*/
#include <cstdio>
#include <cassert>
#include <cmath>
#define MAXN 31
#define MAXL 31
unsigned N,L,I;
unsigned dp[MAXN+1][MAXL+1];

unsigned setsize(int n, int l){
  if (n == 0)
    return 0;
  if (l == 0)
    return 1;
  if (n <= l)
    return (unsigned) pow(2,n);
  if (dp[n][l])
    return dp[n][l];
  dp[n][l] = setsize(n-1,l)+setsize(n-1,l-1);
  return dp[n][l];
}

int main(){
  FILE *fin = fopen("kimbits.in","r");
  FILE *fout = fopen("kimbits.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%u%u%u",&N,&L,&I);
  fclose(fin);
  char buf[100];
  unsigned size, n = N, l = L, i = I;
  while (n > 0){
    size = setsize(n-1,l);
    // printf("%d %d %d %d\n",n,l,i,size);
    // if size >= i, then we know i'th is within that set
    if (i == 1 || size >= i){
      buf[N-n] = '0';
    }
    else{ // if size < i, the i'th element is not in the set
      buf[N-n] = '1';
      i -= size;
      l--;
    }
    n--;
  }
  buf[N] = '\0';
  fprintf(fout,"%s\n",buf);
  fclose(fout);
  return 0;
}
