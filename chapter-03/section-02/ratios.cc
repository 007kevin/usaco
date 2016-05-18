/*
ID: min_j
LANG: C++
TASK: ratios
Date: 18/05/2015
Anaylsis:
*/
#include <cstdio>
#include <cassert>
#define NRAT 3;
int goal[NRAT];
int mix[4][NRAT];

int main(){
  FILE *fin = fopen("ratios.in","r");
  FILE *fout = fopen("ratios.out","w");
  assert(fin != NULL && fout != NULL);
  fscanf(fin,"%d %d %d", goal,goal+1,goal+2);
  for (int i = 1; i <= 3; ++i)
    fscanf(fin,"%d %d %d", mix[i],mix[i]+1,mix[i]+2);
  fclose(fin);

  

  fclose(fout);
  return 0;
}
