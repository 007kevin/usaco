/*
ID: min_j
LANG: C++
TASK: ratios
Date: 18/05/2015
Anaylsis:
  This problem was easy. Since unit numbers cannpt be greater than 100,
  solution is O(100^3), which is well within the running time.
  The trickiest part was dealing with 0's
*/
#include <cstdio>
#include <cassert>
#include <climits>
#define NRAT 3
#define INF INT_MAX
int goal[NRAT];
int mix[3][NRAT];

int check(int b,int o,int w){
  int comb[3] = {0,0,0};
  for (int i = 0; i < 3; ++i)
    comb[i]+=b*mix[0][i];
  for (int i = 0; i < 3; ++i)
    comb[i]+=o*mix[1][i];
  for (int i = 0; i < 3; ++i)
    comb[i]+=w*mix[2][i];

  for (int i = 0; i < 3; ++i){
    if (comb[i] == 0 || goal[i] == 0)
      if (comb[i] != goal[i])
        return 0;
      else
        continue;
    if (comb[i]%goal[i] != 0)
      return 0;
  }

  int div = 0;
  for (int i = 0; i < 3; ++i){
    if (comb[i] == 0)
      continue;
    if (div != 0 && comb[i]/goal[i] != div)
      return 0;
    else
      div = comb[i]/goal[i];
  }
  for (int i = 0; i < 3; ++i)
    if (comb[i] != 0 && goal[i] != 0)
      return comb[i]/goal[i];
}

int main(){
  FILE *fin = fopen("ratios.in","r");
  FILE *fout = fopen("ratios.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%d %d %d", goal,goal+1,goal+2);
  for (int i = 0; i < 3; ++i)
    fscanf(fin,"%d %d %d", mix[i],mix[i]+1,mix[i]+2);
  fclose(fin);

  int cur,min=INF,b,o,w,n;
  for (int i = 0; i < 100; ++i)
    for (int j = 0; j < 100; ++j)
      for (int k= 0; k < 100; ++k){
        if ((cur = check(i,j,k)) && i+j+k < min){
          min = i+j+k;
          b=i;o=j;w=k;n=cur;
        }
      }
  if (min != INF)
    fprintf(fout,"%d %d %d %d\n",b,o,w,n);
  else
    fprintf(fout,"NONE\n");
  fclose(fout);
  return 0;
}
