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
bool subfield[MAXN][MAXN][MAXN];
int squares[MAXN];

bool solve(int a, int b, int m){
  if (m < 1)
    return field[a][b] == 1;
  if (subfield[m][N-m+1][N-m+1]){
    bool edible = true;
    for (int i = a; i < a+2; ++i)
      for (int j = b; j < b+2; ++j)
        if (!subfield[m][i][j])
          return false;
    return true;
  }

  for (int i = a; i < N-m+1; ++i)
    for (int j = b; j < N-m+1; ++j){
      if (solve(i,j,m-1)){
        subfield[m][i][j] = 1;
        squares[m]++;
      }
      else
        subfield[m][i][j] = 0;
    }
  subfield[m][N-m+1][N-m+1] = 1;

  // cout << m << endl;
  // for (int i = 0; i < N-m+1; ++i){
  //   for (int j = 0; j < N-m+1; ++j){
  //     cout<<subfield[m][i][j];
  //   }
  //   cout<<endl;
  // }
  // cout<<endl;

  bool edible = true;
  for (int i = a; i < a+2; ++i)
    for (int j = b; j < b+2; ++j)
      if (!subfield[m][i][j])
        return false;
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
