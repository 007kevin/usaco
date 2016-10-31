/*
ID: min_j
LANG: C++
TASK: shuttle
Date: 10/27/2016
Anaylsis:
*/
#include <cstdio>
#include <cassert>
#include <vector>
#define MAXN 12
using namespace std;
vector<int> S;
int B[2*MAXN+1];
int n;

void move(int i, int p){
  if (i == 0) return;
  int s = 0, t;
  while (B[s]) s++;
  t = s;
  while (B[t] != p) p == 1 ? t-- : t++;
  S.push_back(t+1);
  int tmp = B[t];
  B[t] = B[s];
  B[s] = tmp;
  move(i-1,p);
}

int main(){
  FILE *fin = fopen("shuttle.in","r");
  FILE *fout = fopen("shuttle.out","w");
  assert(fin != NULL);
  assert(fout != NULL);
  fscanf(fin,"%d",&n);
  for (int i = 0; i < (2*n+1)/2; ++i)       B[i] = 1;
  for (int i = (2*n+1)/2+1; i < 2*n+1; ++i) B[i] = 2;
  for (int i = 0; i < n; ++i)
    move(i+1,i%2+1);
  move(n,n%2+1);
  for (int i = n-1; i >= 0; --i)
    move(i+1,i%2+1);
  for(int i = 0; i < S.size(); ++i){
    fprintf(fout,"%d",S[i]);
    if ((i+1)%20 == 0 || i == S.size()-1)
      fprintf(fout,"\n");
    else
      fprintf(fout," ");      
      
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
