/*
ID: min_j
LANG: C++
TASK: rockers
Date: 21/06/2016
Anaylsis:
  We will group songs together (while still
  mainintain order) and perform 0/1 knapsack
  on each grouping to get their value (with max size 
  T). We then choose the M groupings of highest value.
  We do this for all possible groupings of songs to
  find the optimal disk set.

*/
#include <iostream>
#include <fstream>
#include <cassert>
#define MAXN 21
#define MAXT 21
#define MAXM 20
using namespace std;
int N,T,M;
int songs[MAXN];
int value[MAXN];
int I = 0;

int max(int a, int b){
  return a < b ? b : a;
}

void evaluate(int l, int r){
  int dp[r-l+2][T+1];
  for (int i = 0; i <= T; ++i)   dp[0][i] = 0;
  for (int i = 0; i <= r-l+1; ++i) dp[i][0] = 0;
  for (int i = 1; i <= r-l+1; ++i)
    for (int j = 1; j <= T; ++j)
      if (songs[i+l-1] > j)
        dp[i][j] = dp[i-1][j];
      else
        dp[i][j] = max(dp[i-1][j],dp[i-1][j-songs[i+l-1]]+1);
  for (int i = 0; i <= r-l+1; ++i){
    for (int j = 0; j <= T; ++j)
      cout << dp[i][j] << " ";
    cout << endl;
  }
        
  cout << "result" << endl;
  cout << dp[r-l+1][T] << endl;
  
}
  

int main(){
  ifstream fin("rockers.in");
  ofstream fout("rockers.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>T>>M;
  for (int i = 0; i < N; ++i)
    fin>>songs[i];
  fin.close();
  cout << N << " " << T << " " << M << endl;
  evaluate(0,N-1);

  fout.close();
  return 0;
}
