/*
ID: min_j
LANG: C++
TASK: cowtour
Date: 01/05/2015
Anaylsis:
  Find the most center pasture of each field, 
  perform floyd warshal algorithm,
  get largest shortest pair, profit

  Note: 
  Adding a pasture to form a bigger field does not
  necessarily mean the diameter will increase. If
  the joined field does not result in a bigger diameter
  than the solution was already the max diameter of the
  two fields before they were joined.

*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
//#define DEBUG
#define MAXP 150
#define inf DBL_MAX
#define max(a,b) ((a) > (b) ? a : b)

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

  floydwarshall();

  // mark the components/pastures
  int comp = 1;
  for (int i = 0; i < P; ++i)
    if (pasture[i].c == 0){
      mapc(i,comp++);
    }
      
  // find the diameters of the components/pastures
  double sub_pastures[comp-1];
  for (int i = 0; i < comp-1; ++i)
    sub_pastures[i] = 0;
  for (int i = 0; i < P; ++i)
    for (int j = 0; j < P; ++j){
      if (pasture[i].c == pasture[j].c && matrix[i][j] > sub_pastures[pasture[i].c])
        sub_pastures[pasture[i].c] = matrix[i][j];
    }

#ifdef DEBUG
  for (int i = 0; i < comp-1; ++i)
    printf("%f ", sub_pastures[i]);
  printf("\n");
#endif
  
  // iterate through every pair of vertices from the
  // different components, determine its longest paths
  // and find the minimum longest path as the solution
  double sol = inf;
  for (int i = 0; i < P; ++i)
    for (int j = 0; j < P; ++j){
      if (pasture[i].c != pasture[j].c){
        double max1 = 0;
        double max2 = 0;
        for (int k = 0; k < P; ++k){
          if (matrix[i][k] < inf)
            max1 = matrix[i][k] > max1 ? matrix[i][k] : max1;
          if (matrix[j][k] < inf)
            max2 = matrix[j][k] > max2 ? matrix[j][k] : max2;
        }
        double newdist = max1+dist(pasture[i],pasture[j])+max2;
        if (newdist > sub_pastures[pasture[i].c] && newdist > sub_pastures[pasture[j].c])
          sol = newdist < sol ? newdist : sol;
        else
          sol = max(sub_pastures[pasture[i].c],sub_pastures[pasture[j].c]) < sol ? max(sub_pastures[pasture[i].c],sub_pastures[pasture[j].c]) : sol;
      }
        
    }

  fprintf(fout,"%6.6f\n",sol);

#ifdef DEBUG  
  for (int i = 0; i < P; ++i){
    for (int j = 0; j < P; ++j){
      if (matrix[i][j] != inf)
        printf("%d", pasture[i].c);
      else
        if (matrix[i][j] == inf)
          printf("8");
        else
          printf("0");
    }
      //      printf("%4.0f",matrix[i][j] != inf ? matrix[i][j] : 0 );
    printf("\n");
  }
#endif

  return 0;
}
