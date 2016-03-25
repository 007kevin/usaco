/*
ID: min_j
LANG: C++
TASK: combo
Date: 09/03/2015
Comment:
Could not get this solution to work for dial < 5. 
*/
#include <stdio.h>

int getadj(int dial, int n){
  int r = n%dial;
  if (r == 0)
    return dial;
  if (r < 0)
    return r+dial;
  return r;
}

int main(){
  FILE *fin = fopen("combo.in", "r");
  FILE *fout = fopen("combo.out", "w");
  int dial, fc[3], mc[3], overlap[3];
  fscanf(fin, "%d", &dial);
  fscanf(fin, "%d%d%d", &fc[0], &fc[1], &fc[2]);
  fscanf(fin, "%d%d%d", &mc[0], &mc[1], &mc[2]);
  for (int i = 0; i < 3; ++i)
    overlap[i] = 0;

  // Get number of overlapping combinations
  for (int i = 0; i < 3; ++i){
    for (int j = -2; j <= 2; ++j){
      int cmp = getadj(dial, j+fc[i]);
      for (int k = -2; k <= 2; ++k){
        if (cmp == getadj(dial, k+mc[i]))
          overlap[i]++;
      }
    }
  }

  for (int i = 0; i < 3; ++i)
    printf("%d ", overlap[i]);
  printf("\n");

  int dup = 1;
  for (int i = 0; i < 3; ++i)
    dup *= overlap[i];

  fprintf(fout, "%d\n", 125*2 - dup);

  fclose(fin);
  fclose(fout);
  return 0;
}
