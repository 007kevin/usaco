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
int matrix[MAXN][2][MAXN];
int visit[2][MAXN];
int slen[MAXN];

void find(int s, int c, int p){
  if (p > sol) return;
  if (s == c && p != 0){
    sol = min(sol,p);
    cout << sol << endl;
    return;
  }
  if (!visit[0][c]){
    for (int i = 1; i <= N; ++i){
      if (matrix[c][0][i]){
        visit[0][c] = 1;
        if (matrix[i][0][c])
          visit[0][i] = 1;
        else
          visit[1][i] = 1;
        find(s,i,p+slen[c]);
        if (matrix[i][0][c])
          visit[0][i] = 0;
        else
          visit[1][i] = 0;
        visit[0][c] = 0;
      }
    }
  }
  if (!visit[1][c]){
    for (int i = 1; i <= N; ++i){
      if (matrix[c][1][i]){
        if (matrix[i][1][c])
          visit[1][i] = 1;
        else
          visit[0][i] = 1;
        visit[1][c] = 1;
        find(s,i,p+slen[c]);
        if (matrix[i][1][c])
          visit[1][i] = 0;
        else
          visit[0][i] = 0;
        visit[1][c] = 0;
      }
    }
  }
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
      matrix[s_num][0][e] = 1;
    }
    for (int j = 0; j < N2; ++j){
      fin>>e;
      matrix[s_num][1][e] = 1;
    }
  }
  for (int i = 1; i <= N; ++i){
    cout << i << " ============" << endl;
    visit[0][i] = 1;
    find(i,i,0);
  }
  fin.close();

  find(1,1,0);

  fout << sol << endl;
  fout.close();
  return 0;
}
