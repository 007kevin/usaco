/*
ID: min_j
LANG: C++
TASK: shopping
Date: 25/05/2015
Anaylsis:
  For each special offer, we calculated the amount saved,
  then apply greedy algorithm against the items required.

  What happens when the amount saved are the same for
  different special offers? 
    - Should we choose the one that optimally allows the
      choosing of other special offers down the road?
      - Anytime we come across special offers of the same price,
        attempt all combinations of taking those special offers
        
*/
#include <cstdio>
#include <cassert>
#include <algorithm>
#define DEBUG
#define MAXN 5
#define MAXS 99
#define MAXC 999
using namespace std;
struct special_offer{
  int n,r,p; // #products, reduced priced, actual price
  int c[MAXN],k[MAXN]; // prod. code, #items
  bool operator<(const special_offer& rhs) const {
    return p-r > rhs.p - rhs.r;
  }
};
special_offer S[MAXS];
int s;
int amt[MAXC+1];
int price[MAXC+1];
  
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
  }

  // Sort the special offers by amount saved
  sort(S,S+s);
  
#ifdef DEBUG
  printf("s\tr\tp\tp-r\tn\tc\tk\n");
  for (int i = 0; i < s; ++i){
    printf("%d\t%d\t%d\t%d\t%d\tc\tk\n",
           i,S[i].r,S[i].p,S[i].p-S[i].r,S[i].n);
    for (int j = 0; j < S[i].n; ++j)
      printf(" \t \t \t \t%d\t\%d\n",
             S[i].c[j],S[i].k[j]);
  }
#endif
  
  int solution = 0;
  for (int i = 0; i < s; ++i){
    cur = &S[i];
    int flag = 1;
    for (int j = 0; j < cur->n; ++j){
      if (amt[cur->c[j]] - cur->k[j] < 0){
        flag = 0; break;
      }
    }
    if (flag){
      for (int j = 0; j < cur->n; ++j){
        amt[cur->c[j]]-=cur->k[j];
      }
      solution+=cur->r;
      i--; // Try again on the current special offer
    }
  }
  for (int i = 1; i <= MAXC; ++i)
    solution+=amt[i]*price[i];

  fprintf(fout,"%d\n",solution);

  fclose(fout);
  return 0;
}

