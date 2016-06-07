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

void solve(int m){
  if (m < 2)
    return;
  for (int i = 0; i+m <= N; ++i)
    for (int j = 0; j+m <= N; ++j){
      bool ravaged = false;
      for (int k = i; k <= m; ++k){
        for (int l = j; l <= m; ++l)
          if (field[k][l] == 0){
            ravaged = true;
            break;
          }
        if (ravaged)
          break;
      }
      if (!ravaged){
        squares[m]++;
      }
    }
  solve(m-1);
}


int main(){
  ifstream fin("range.in");
  ofstream fout("range.out");
  fin>>N;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      fin>>field[i][j];
  solve(N);
  for (int i = 2; i <= N; ++i)
    fout << i << " " << squares[i] << endl;
 
  
}
