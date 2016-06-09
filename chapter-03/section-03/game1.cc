/*
ID: min_j
LANG: C++
TASK: game1
Date: 09/06/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#define MAXN 1201
#define max(a,b) (a) < (b) ? b : a
using namespace std;
int N;
int board[MAXN];

int solve(int p,int l, int r){
  if (l == r)
    return board[l];
  int res = max(solve((p+1)%2,l+1,r),solve((p+1)%2,l,r-1));
  cout << res << endl;
                
  return res;
}

int main(){
  ifstream fin("game1.in");
  ofstream fout("game1.out");
  fin>>N;

  
  for (int i = 1; i <= N; ++i)
    fin>>board[i];
  solve(0,1,N);
  return 0;
}


