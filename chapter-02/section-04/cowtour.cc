/*
ID: min_j
LANG: C++
TASK: cowtour
Date: 01/05/2015
Anaylsis:
*/

#include <stdio.h>
#define MAXP 150

int P;
struct p {
  int x,y;
};
struct p pasture[MAXP];
int matrix[MAXP][MAXP];

int main(){
  FILE *fin = fopen("cowtour.in", "r");
  FILE *fout = fopen("cowtour.out", "w");
  fscanf(fin,"%d",&P);
  for (int i = 0; i < P; ++i)
    fscanf(fin,"%d %d",&pasture[i].x,&pasture[i].y);
  char c;
  for (int i = 0; i < P; ++i)
    for (int j = 0 ; j < P; ++j){
      while((c = fgetc(fin)) == '\n');
      matrix[i][j] = c-'0';
    }

  for (int i = 0; i < P; ++i){
    for (int j = 0; j < P; ++j)
      printf("%d",matrix[i][j]);
    printf("\n");
  }
  return 0;
}
