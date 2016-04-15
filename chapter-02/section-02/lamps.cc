/*
ID: min_j
LANG: C++
TASK: lamps
Date: 15/04/2015
Anaylsis:
  Order of the buttons pressed does not matter. Also, pressing
  a button twice is the same as no presses at all. Therefore
  there can be at most 2^4 = 16 combinations of button presses.
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 100
int N, C, si;
char L[MAXN+1], F[MAXN+1];
char *solution[1000];

void toggle(){
  for (int i = 0; i < N; ++i)
    L[i] = L[i] == '0' ? '1' : '0';
}
void odd(){
  for (int i = 0; i < N; i+=2)
    L[i] = L[i] == '0' ? '1' : '0';
}
void even(){
  for (int i = 1; i < N; i+=2)
    L[i] = L[i] == '0' ? '1' : '0';
}
void k(){
  for (int i = 0; 3*i < N; i++)
    L[3*i] = L[3*i] == '0' ? '1' : '0';
}

bool correct(){
  for (int i = 0; i < N; ++i){
    if (F[i] != '*'){
      if (F[i] != L[i])
        return false;
    }
  }
  return true;
}

bool compare(char *a, char *b){
  for (int i = 0; i < N; ++i){
    if (a[i] == '0' && b[i] == '1')
      return true;
    if (a[i] == '1' && b[i] == '0')
      return false;
  }
  return false;
}

void solve(int c){
  if (c == 0){
    if (correct())
      solution[si++] = strdup(L);
    return;
  }
  toggle(); solve(c-1); toggle();
  odd();    solve(c-1); odd();
  even();   solve(c-1); even();
  k();      solve(c-1); k();
}


int main(){
  ifstream fin("lamps.in");
  ofstream fout("lamps.out");
  fin>>N>>C;

  // initialize
  for (int i = 0; i < N; ++i){
    F[i] = '*';
    L[i] = '1';
  }
  F[N] = L[N] = '\0';
    
  int l;
  fin>>l;
  while(l != -1){
    F[l-1] = '1';
    fin>>l;
  }
  fin>>l;
  while(l != -1){
    F[l-1] = '0';
    fin>>l;
  }
  solve(C < 4 ? C : 4);
  sort(solution, solution + si, compare);
  if (si > 0){
    char *last = solution[0];
    fout << last << endl;
    for (int i = 1; i < si; ++i)
      if (strcmp(last, solution[i]) != 0){
        fout << solution[i] << endl;
        last = solution[i];
      }
  }
  if (si == 0)
    fout << "IMPOSSIBLE" << endl;

  return 0;
}
