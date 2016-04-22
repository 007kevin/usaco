/*
ID: min_j
LANG: C++
TASK: nocows
Date: 17/04/2015
Anaylsis:
  The degree of each node is 0 or 2, therefore
  N must be odd (i.e 1,3,5,7)

  The recurrence relation are the subtrees!

  Not sure for this solution why we are
  dp[N][K]-dp[N][K-1] before output??
  
  Solution file prefixed with 'REDO' so that
  I come back to this later and understand


*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#define MAXN 201 // 3 <= N < 200
#define MAXK 101 // 1 < K < 100
#define MODULO 9901
int N,K;
unsigned long long dp[MAXN][MAXK];

int main(){
  ifstream fin("nocows.in");
  ofstream fout("nocows.out");
  fin>>N>>K;

  for (int k = 1; k <= K; ++k){
    dp[1][k] = 1; // loop on heights
    for (int n = 2; n <= N; ++n){
      dp[n][k] = 0; // loop on nodes
      for (int p = 1; p <= n-2; ++p){ // loop on previous nodes
        dp[n][k] += dp[p][k-1] * dp[n-1-p][k-1];
        dp[n][k] %= MODULO;
      }
    }
    
    // for (int i = 1; i <= N; ++i){
    //   for (int j = 1; j <= K; ++j)
    //     cout << dp[i][j] << " ";
    //   cout << endl;
    // }
    // cout << "-----------" << endl;

  }

  fout << ((dp[N][K]+MODULO)-dp[N][K-1])%MODULO << endl;
  
  return 0;
}
