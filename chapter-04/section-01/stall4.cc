/*
ID: min_j
LANG: C++
TASK: stall4
Date: 19/07/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <cassert>
#define MAX 202
using namespace std;
int N,M,sol;
int matrix[MAX][MAX];
int augment_path(int n){
  if (n == N+M+1){
    sol++;
    return 1;
  }
  for (int i = 1; i <= N+M+1; ++i)
    if (matrix[n][i] && augment_path(i))
      matrix[n][i] = 0;
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
  while(augment_path(0));
  fout << sol << endl;
  fout.close();
  return 0;
}
