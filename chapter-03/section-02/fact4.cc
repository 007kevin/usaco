/*
ID: min_j
LANG: C++
TASK: fact4
Date: 13/05/2015
Anaylsis:
*/
#include <cstdio>
#include <cassert>
#define MAXN 4220
int N;
int dp[MAXN+1]; // dp[i] is the right most non-zero digit of i
int main(){
  FILE *fin  = fopen("fact4.in","r");
  FILE *fout = fopen("fact4.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%d",&N);
  int i = 1;
  dp[1] = 1;
  while (++i <= N+1){
    long next = dp[i-1]*i;
    while (next%10 == 0)
      next/=10;
    dp[i] = next%10;
  }
  double cur = 1;
  for (int i = 1; i <= N; ++i){
    cur*=i;
    printf("%d %d: %.0f\n",i,dp[i],cur);
  }
  fprintf(fout,"%d\n",dp[N]);
  return 0;
}
