/*
ID: min_j
LANG: C++
TASK: shuttle
Date: 10/27/2016
Anaylsis:
*/
#include <cstdio>
#include <cassert>
#define MAXN 12
char B[2*MAXN+1];
int n;

void move(int i, int dir){
  
}

int main(){
  FILE *fin = fopen("shuttle.in","r");
  FILE *fout = fopen("shuttle.out","w");
  assert(fin != NULL);
  assert(fout != NULL);
  fscanf(fin,"%d",&n);
  for (int i = 0; i < s; ++i)       B[i] = 'w';
  for (int i = s+1; i < 2*n+1; ++i) B[i] = 'b';
  for (int i = 1; i <= n-1; ++i)
    move(i,i%2);
  
    
  fclose(fin);
  fclose(fout);
  return 0;
}
