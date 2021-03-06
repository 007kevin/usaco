n/*
ID: min_j
LANG: C++
TASK: stall4
Date: 19/07/2016
Anaylsis:
  Note - When applying the ford-fulkerson algorithm, it is
         important to maintain skew symmetry and also to keep 
         track of visited vertices to prevent infinite loops
*/
#include <iostream>
#include <fstream>
#include <cassert>
#define MAX 402
using namespace std;
int N,M,sol;
int matrix[MAX][MAX];
int visit[MAX];
int augment_path(int n){
  visit[n] = 1;
  if (n == N+M+1){
    sol++;
    return 1;
  }
  for (int i = 1; i <= N+M+1; ++i)
    if (visit[i] == 0 && matrix[n][i] && augment_path(i)){
      matrix[n][i]--;
      matrix[i][n]++;      
      return 1;
    }
  return 0;
}
int main(){
  ifstream fin("stall4.in");
  ofstream fout("stall4.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>M;
  int s,n;
  for (int i = 1; i <= N; ++i){
    fin>>s;
    for (int j = 0; j < s; ++j){
      fin>>n;
      matrix[i][N+n] = 1;
    }
  }
  for (int i = 1; i <= N; ++i)
    matrix[0][i] = 1;
  for (int i = N+1; i <= N+M; ++i)
    matrix[i][N+M+1] = 1;
  fin.close();
  while(augment_path(0)){
    for (int i = 0; i <= N+M+1; ++i)
      visit[i] = 0;
  }
  fout << sol << endl;
  fout.close();
  return 0;
}
