/*
ID: min_j
LANG: C++
TASK: stamps
Date: 11/05/2015
Anaylsis:
We keep an array "dp" such that dp[i] is 
the minimum number of stamps needed to make i cents. 
For each stamp type, we try adding one stamp of that 
type to each number of cents that we have already made. 

*/
#include <cstdio>
#include <cassert>
#define MAXK 200
#define MAXS 2000000
int stamp[MAXK+1];
int dp[MAXS+1];
int K,N,I;

int main(){
  FILE *fin = fopen("stamps.in","r");
  FILE *fout = fopen("stamps.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%d %d",&K,&N);
  for (int i = 0; i < N; ++i)
    fscanf(fin,"%d",stamp+i);
  fclose(fin);

  int i;
  for (i = 0; i <= MAXS; ++i){
    if (i != 0 && dp[i] == 0)
      break;
    if (i == 0 || dp[i] < K)
      for (int j = 0; j < N; ++j){
        if (dp[i+stamp[j]] != 0)
          dp[i+stamp[j]] = dp[i+stamp[j]] > dp[i] + 1 ? dp[i]+1 : dp[i+stamp[j]];
        else
          dp[i+stamp[j]] = dp[i]+1;
      }
  }
  fprintf(fout,"%d\n",i-1);

  // for (int i = 0; i < 100; ++i)
  //   printf("%d: %d\n",i,dp[i]);
  
  fclose(fout);
}
