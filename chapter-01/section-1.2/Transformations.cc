/*
ID: min_j
LANG: C++
TASK: transform
Date: 19/02/2015
*/
#include<stdio.h>
#include<stdlib.h>

void printsq(char **a, int size){
  for (int i = 0; i < size; ++i){
    for (int j = 0; j < size; ++j)
      putchar(a[i][j]);
    putchar('\n');
  }
}
void freesq(char **a, int size){
  for (int i = 0; i < size; ++i)
    free(a[i]);
  free(a);
}
int isequal(char **a, char **b, int size){
  for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
           if (a[i][j] != b[i][j]) return 0;
  return 1;
}
char** rotate(char **a, int size){
  char **b;
  b = (char **) malloc(size * sizeof(char*));
  for (int i = 0; i < size; ++i){
    b[i] = (char*) malloc(size);
    for (int j = 0; j < size; ++j)
      b[i][j] = a[size - j - 1][i];
  }
  return b;
}
char** reflectv(char **a, int size){
  char **b;
  b = (char**) malloc(size * sizeof(char*));
  for (int i = 0; i < size; ++i){
    b[i] = (char*) malloc(size);
    for (int j = 0; j < size; ++j)
      b[i][j] = a[size - i - 1][j];
  }
  return b;
}

int main(){
  FILE *fin = fopen("transform.in", "r");
  FILE *fout = fopen("transform.out", "w");
  int n;

  fscanf(fin, "%d", &n);
  char **a, **b;
  a = (char**)  malloc(n * sizeof(char*));
  for (int i = 0; i < n; ++i){
    a[i] = (char*) malloc(n + 1);
    fscanf(fin, "%s", a[i]);
  }
  b = (char**) malloc(n * sizeof(char*));
  for (int i = 0; i < n; ++i){
    b[i] = (char*) malloc(n + 1);
    fscanf(fin, "%s", b[i]);
  }

  char **r90 = rotate(a, n);
  char **r180 = rotate(r90, n);
  char **r270 = rotate(r180, n);

  char **ra = reflectv(a, n);

  char **c90 = reflectv(r90, n);
  char **c180 = reflectv(r180, n);
  char **c270 = reflectv(r270, n);

  // printsq(a, n);
  // printf("************\n");  
  // printsq(r90, n);
  // putchar('\n');
  // printsq(r180, n);
  // putchar('\n');
  // printsq(r270, n);
  // printf("************\n");
  // printsq(ra, n);
  // printf("************\n");  
  // printsq(c90, n);
  // putchar('\n');
  // printsq(c180, n);
  // putchar('\n');
  // printsq(c270, n);
  // printf("************\n");    
  // printsq(b, n);
  
  if (isequal(r90, b, n))
    fprintf(fout, "1\n");
  else if (isequal(r180, b, n))
    fprintf(fout, "2\n");
  else if (isequal(r270, b, n))
    fprintf(fout, "3\n");
  else if (isequal(c180, b, n))
    fprintf(fout, "4\n");
  else if (isequal(c90, b, n) || isequal(ra, b, n) || isequal(c270, b, n))
    fprintf(fout, "5\n");
  else if (isequal(a, b, n))
    fprintf(fout, "6\n");
  else
    fprintf(fout, "7\n");
    
  freesq(a, n);
  freesq(b, n);
  freesq(r90, n);
  freesq(r180, n);
  freesq(r270, n);
  freesq(c90, n);
  freesq(c180, n);
  freesq(c270, n);
  fclose(fin);
  fclose(fout);
  return 0;
}
