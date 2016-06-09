/*
ID: min_j
LANG: C++
TASK: range
Date: 07/06/2016
Anaylsis:
  Find the biggest unravaged field, mark it,
  then iterate the unvisited?
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXN 251
int N;
int field[MAXN][MAXN];
int squares[MAXN];

bool solve(int a, int b, int m){
  if (m < 1)
    return field[a][b] == 1;

  int subfield[N-m+1][N-m+1];
  for (int i = 0; i < N-m+1; ++i)
    for (int j = 0; j < N-m+1; ++j){
      if (solve(i,j,m-1)){
        subfield[i][j] = 1;
        squares[m]++;
      }
      else
        subfield[i][j] = 0;
    }
  for (int i = 0; i < N-m+1; ++i){
    for (int j = 0; j < N-m+1; ++j){
      if (subfield[i][j] == 0)
        return false;
    }
  }
  return true;
}


int main(){
  ifstream fin("range.in");
  ofstream fout("range.out");
  fin>>N;
  char c;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j){
      fin>>c;
      field[i][j] = c-'0';
    }
  solve(0,0,N);
  for (int i = 2; i <= N; ++i)
    if (squares[i])
      fout << i << " " << squares[i] << endl;
}
