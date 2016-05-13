/*
ID: min_j
LANG: C++
TASK: fact4
Date: 13/05/2015
Anaylsis:
  Since max N is 4220, we can keep modding by 10000 as we build up the N
  factorial.
  The solution insight though was to eliminate 2's and 5's in the factorial's
  product so that values don't end in 10. For every number of 2's that were avoided, 
  the same amount of 5 must de done
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
    dp[i] = next%10000;
  }
  // double cur = 1;
  // for (int i = 1; i <= N; ++i){
  //   cur*=i;
  //   printf("%d %d: %.0f\n",i,dp[i],cur);
  // }
  fprintf(fout,"%d\n",dp[N]%10);
  return 0;
}
