/*
ID: min_j
LANG: C++
TASK: fence9
Date: 11/07/2016
Anaylsis:
  Build an adjacency matrix of fence endpoints
  as nodes and fence length as weights. Recursively
  iterate through each node until smallest perimeter 
  is found.
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <climits>
#define min(a,b) ((a) < (b) ? a : b)
#define MAXN 101
using namespace std;
int N, sol = INT_MAX;
int matrix[MAXN][MAXN];
int slen[MAXN];

void find_smallest_perimeter(int n, int m, int p){
  if (p > sol) return;
  if (n == m && p != 0){
    sol = min(sol,p);
    return;
  }
  for (int i = 1; i <= N; ++i)
    if (matrix[m][i] && m != i)
      find_smallest_perimeter(n,i,p+slen[m]);
}

int main(){
  ifstream fin("fence6.in");
  ofstream fout("fence6.out");
  assert(fin.is_open());
  assert(fout.is_open());
  int N1,N2,s_num,len,e;
  fin>>N;
  for (int i = 0; i < N; ++i){
    fin>>s_num>>len>>N1>>N2;
    slen[s_num] = len;
    for (int j = 0; j < N1; ++j){
      fin>>e;
      matrix[s_num][e] = 1;
    }
    for (int j = 0; j < N2; ++j){
      fin>>e;
      matrix[s_num][e] = 1;
    }
  }
  fin.close();
  
  for (int i = 1; i <= N; ++i){
    find_smallest_perimeter(i,i,0);
  }

  cout << "\t";
  for (int i = 0; i <= N; ++i)
    cout << i << " ";
  cout << endl;
  for (int i = 0; i <= N; ++i){
    cout << i << "\t";
    for (int j = 0; j <= N; ++j){
      if (matrix[i][j] == 0)
        cout << "  ";
      else
        cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  for (int i = 0; i <= N; ++i)
    cout << i << "\t";
  cout << endl;
  for (int i = 0; i <= N; ++i)
    cout << slen[i] << "\t";
  cout << endl;

  fout << sol << endl;
  fout.close();
  return 0;
}
