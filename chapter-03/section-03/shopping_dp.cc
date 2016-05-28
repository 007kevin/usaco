/*
ID: min_j
LANG: C++
TASK: shopping
Date: 25/05/2015
Anaylsis:
*/
#include <cstdio>
#include <cassert>
#include <climits>
//#define DEBUG
#define MAXN 5
#define MAXS 99
#define MAXC 999
using namespace std;
struct special_offer{
  int n,r,p,s; // #products, reduced priced, actual price, savings
  int c[MAXN],k[MAXN]; // prod. code, #items
};
special_offer S[MAXS];
int s,solution = INT_MAX;
int amt[MAXC+1];
int price[MAXC+1];

int solve(int I){
  int p = 0;
  if (I == 0){
    for (int i = 0; i < MAXC; ++i)
      p+=amt[i]*price[i];
    return p;
  }
  p = solve(I-1);
}
  
int main(){
  FILE *fin = fopen("shopping.in","r");
  FILE *fout = fopen("shopping.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%d",&s);
  for (int i = 0; i < s; ++i){
    fscanf(fin,"%d",&S[i].n);
    for (int j = 0; j < S[i].n; ++j)
      fscanf(fin,"%d %d",&S[i].c[j],&S[i].k[j]);
    fscanf(fin,"%d",&S[i].r);
  }
  int b;
  fscanf(fin,"%d",&b);
  int code;
  for (int i = 0; i < b; ++i){
    fscanf(fin,"%d",&code);
    fscanf(fin,"%d%d",&amt[code],&price[code]);
  }
  fclose(fin);
  // Set the actual price of special offers
  special_offer *cur;
  for (int i = 0; i < s; ++i){
    cur = &S[i];
    int actual = 0;
    for (int j = 0; j < cur->n; ++j)
      actual+=price[cur->c[j]]*cur->k[j];
    cur->p = actual;
    cur->s = cur->p - cur->r;
  }

#ifdef DEBUG
  printf("s\tr\tp\ts\tn\tc\tk\n");
  for (int i = 0; i < s; ++i){
    printf("%d\t%d\t%d\t%d\t%d\tc\tk\n",
           i,S[i].r,S[i].p,S[i].s,S[i].n);
    for (int j = 0; j < S[i].n; ++j)
      printf(" \t \t \t \t%d\t\%d\n",
             S[i].c[j],S[i].k[j]);
  }
#endif
  solve(s);
  fprintf(fout,"%d\n",solution);
  fclose(fout);
  return 0;
}

