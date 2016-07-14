/*
ID: min_j
LANG: C++
TASK: fence6
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
using namespace std;

#define MAXN 101
int len[MAXN];
int con[MAXN][MAXN][2]; // for con[i][[j][0] = 1 means segment i
                        // is connected to segment j through endpoint 0
                        // of i
int visit[MAXN][2];
int N;
int sol;
void find(int s,int c, int p){
  if (p > sol) return;
  if (s == c && p != 0){
    sol = p < sol ? p : sol;
    return;
  }
  if (visit[c][0] == 0){
    visit[c][0] = 1;
    for (int i = 1; i <= N; ++i){
      if (con[c][i][0]){
        if (con[i][c][0])
          visit[i][0] = 1;
        if (con[i][c][1])
          visit[i][1] = 1;
        find(s,i,p+len[c]);
        if (con[i][c][0])
          visit[i][0] = 0;
        if (con[i][c][1])
          visit[i][1] = 0;
      }
    }
    visit[c][0] = 0;
  }
  else {
    if (visit[c][1] == 0){
      visit[c][1] = 1;
      for (int i = 1; i <= N; ++i){
        if (con[c][i][1]){
          if (con[i][c][0])
            visit[i][0] = 1;
          if (con[i][c][1])
            visit[i][1] = 1;
          find(s,i,p+len[c]);
          if (con[i][c][0])
            visit[i][0] = 0;
          if (con[i][c][1])
            visit[i][1] = 0;
        }
      }
      visit[c][1] = 0;
    }
  }
}

int main(){
  ifstream fin("fence6.in");
  ofstream fout("fence6.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N;
  int s,l,n1,n2,e;
  for (int i = 0; i < N; ++i){
    fin>>s>>l>>n1>>n2;
    sol+=l;
    len[s] = l;
    for (int j = 0; j < n1; ++j){
      fin>>e;
      con[s][e][0] = 1;
    }
    for (int j = 0; j < n2; ++j){
      fin>>e;
      con[s][e][1] = 1;
    }
  }
  fin.close();
  if (N < 3){
    fout << "0" << endl;
    return 0;
  }

  for (int i = 1; i <= N; ++i){
    find(i,i,0);
  }

  fout << sol << endl;
  fout.close();
  return 0;
}
