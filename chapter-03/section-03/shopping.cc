/*
ID: min_j
LANG: C++
TASK: shopping
Date: 25/05/2016
Anaylsis:
  For each special offer, we calculated the amount saved,
  then apply greedy algorithm against the items required.

  What happens when the amount saved are the same for
  different special offers? 
    - Should we choose the one that optimally allows the
      choosing of other special offers down the road?
      - Anytime we come across special offers of the same price,
        attempt all combinations of taking those special offers

  This solution fails on test case 10.. too slow. It looks like
  we must solve via DP
*/
#include <cstdio>
#include <cassert>
#include <algorithm>
//#define DEBUG
#define MAXN 5
#define MAXS 99
#define MAXC 999
using namespace std;
struct special_offer{
  int n,r,p,s; // #products, reduced priced, actual price, savings
  int c[MAXN],k[MAXN]; // prod. code, #items
  bool operator<(const special_offer& rhs) const {
    return s > rhs.s;
  }
};
special_offer S[MAXS];
int s;
int amt[MAXC+1];
int price[MAXC+1];
int memo[MAXS+1];

void solve(int cprice, int I){
  if (memo[I] != 0 && cprice > memo[I])
    return;
  memo[I] = cprice;
  if (I == s)
    return;
  printf("%d\n",cprice);
  special_offer *cur;
  cur = &S[I];
  int flag = 1;
  for (int j = 0; j < cur->n; ++j)
    if (amt[cur->c[j]] - cur->k[j] < 0){
      flag = 0; break;
    }
  if (flag){
    for (int j = 0; j < cur->n; ++j){
      amt[cur->c[j]]-=cur->k[j];
    }
    solve(cprice - cur->s, I);
    for (int j = 0; j < cur->n; ++j){
      amt[cur->c[j]]+=cur->k[j];
    }
  }
  solve(cprice, I+1);
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
  int maxprice = 0;
  for (int i = 1; i <= MAXC; ++i)
    maxprice+=price[i]*amt[i];

  sort(S,S+s);
  solve(maxprice,0);

  fprintf(fout,"%d\n",memo[s]);

  fclose(fout);
  return 0;
}

