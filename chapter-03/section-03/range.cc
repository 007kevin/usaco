/* 
ID: min_j
LANG: C++
TASK: range
Date: 07/06/2016
Anaylsis:
  Recursively break down into the smaller squares until
  we reach size 1. Base of whether that square is ravaged,
  we recursively backtrack to squares of bigger size in 
  which the first square will determine is current square is also
  ravaged/unravaged. We use subfield to keep track of visited
  squares.
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define MAXN 251
int N;
int field[MAXN][MAXN];
vector<vector<vector<bool> > > subfield;
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
  subfield.resize(N+1);
  for (int i = 0; i <= N; ++i){
    subfield[i].resize(N+1);
    for (int j = 0; j <= N; ++j)
      subfield[i][j].resize(N+1);
  }
    
  solve(0,0,N);
  for (int i = 2; i <= N; ++i)
    if (squares[i])
      fout << i << " " << squares[i] << endl;
}
