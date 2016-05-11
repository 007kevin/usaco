/*
ID: min_j
LANG: C++
TASK: stamps
Date: 11/05/2015
Anaylsis:
  We may need to use recursion to keep track
  of the number of stamps
*/
#include <cstdio>
#include <cassert>
#define MAXK 200
int stamp[MAXK+1];
int dp[10000];
int K,N;
int main(){
  FILE *fin = fopen("stamps.in","r");
  FILE *fout = fopen("stamps.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%d %d",&K,&N);
  for (int i = 0; i < N; ++i)
    fscanf(fin,"%d",stamp+i);
  fclose(fin);
  int i;
  for (i = 0; i <= 10000; ++i)
    if (i != 0 && dp[i] == 0)
      break;
    else
      for (int j = 0; j < N; ++j)
        if (i+stamp[j] <= 10000)
          dp[i+stamp[j]]+=stamp[j];
  fprintf(fout,"%d\n",i-1);
  fclose(fout);
}
