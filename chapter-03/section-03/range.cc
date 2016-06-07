/*
ID: min_j
LANG: C++
TASK: range
Date: 07/06/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXN 251
int N;
int field[MAXN][MAXN];
int squares[MAXN];

void solve(int m){
  int offset = 
}


int main(){
  ifstream fin("range.in");
  ofstream fout("range.out");
  fin>>N;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      fin>>squares[i][j];
  solve(N);
 
  
}
