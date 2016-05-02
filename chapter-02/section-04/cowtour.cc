/*
ID: min_j
LANG: C++
TASK: cowtour
Date: 01/05/2015
Anaylsis:
  Find the shortest distance cow walk between
  the two pastures, perform floyd warshal algorithm,
  get largest shortest pair, profit
*/

#include <stdio.h>
#include <math.h>
#include <float.h>
#define DEBUG
#define MAXP 150
#define inf DBL_MAX

int P;
struct p {
  int x,y,c; // x,y coordinates & component number
};
struct p pasture[MAXP];
double matrix[MAXP][MAXP];

double dist(struct p a, struct p b){
  return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

double add(double a, double b){
  if (a == inf || b == inf)
    return inf;
  return a+b;
}

void floydwarshall(){
  for (int k = 0; k < P; ++k)
    for (int i = 0; i < P; ++i)
      for (int j = 0; j < P; ++j)
        if (add(matrix[i][k],matrix[k][j]) < matrix[i][j])
          matrix[i][j] = matrix[i][k] + matrix[k][j];
}

void mapc(int a, int c){
  if (pasture[a].c == 0){
    pasture[a].c = c;
    for (int i = 0; i < P; ++i)
      if (a != i && matrix[a][i] != inf)
        mapc(i,c);
  }
}

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
      if (i != j){
        if (c == '1')
          matrix[i][j] = dist(pasture[i],pasture[j]);
        else
          matrix[i][j] = inf;
      }
    }

  // mark the components/pastures
  for (int i = 0; i < P; ++i)
    if (pasture[i].c == 0){
      mapc(i,1);
      break;
    }
  for (int i = 0; i < P; ++i)
    if (pasture[i].c == 0){
      mapc(i,2);
      break;
    }

  floydwarshall();

#ifdef DEBUG  
  for (int i = 0; i < P; ++i)
    printf("%d ", pasture[i].c);
  printf("\n");
#endif
  
#ifdef DEBUG  
  for (int i = 0; i < P; ++i){
    for (int j = 0; j < P; ++j)
      printf("%4.0f",matrix[i][j] != inf ? matrix[i][j] : 0 );
    printf("\n");
  }
#endif

  return 0;
}
