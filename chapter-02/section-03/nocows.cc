/*
ID: min_j
LANG: C++
TASK: nocows
Date: 17/04/2015
Anaylsis:
  The degree of each node is 0 or 2, therefore
  N must be odd (i.e 1,3,5,7)

  The recurrence relation are the subtrees!
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#define MAXN 200 // 3 <= N < 200
#define MAXK 100 // 1 < K < 100
#define MODULO 9901
int N,K;
unsigned long long table[MAXN][MAXK];

int main(){
  ifstream fin("nocows.in");
  ofstream fout("nocows.out");
  fin>>N>>K;
  table[1][1] = 1;
  for (int n = 1; n <= N; ++n)
    for (int k = 1; k <= K; ++k){
      
      }
    }

  fout << table[N][K]%MODULO << endl;
  
  for (int i = 1; i <= N; ++i){
    for (int j = 1; j <= K; ++j)
      cout << table[i][j] << " ";
    cout << endl;
  }
  
  return 0;
}
