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
#include <algorithm>
#include <cstring>
#define MAXN 21
#define MAXT 21
#define MAXM 20
using namespace std;
int N,T,M;
int songs[MAXN];
int value[MAXN];
int I = 0;
int max_songs = 0;

int max(int a, int b){
  return a < b ? b : a;
}

int evaluate(int l, int r){
  // Get value of song range
  int dp[r-l+2][T+1];
  for (int i = 0; i <= T; ++i)   dp[0][i] = 0;
  for (int i = 0; i <= r-l+1; ++i) dp[i][0] = 0;
  for (int i = 1; i <= r-l+1; ++i)
    for (int j = 1; j <= T; ++j)
      if (songs[i+l-1] > j)
        dp[i][j] = dp[i-1][j];
      else
        dp[i][j] = max(dp[i-1][j],dp[i-1][j-songs[i+l-1]]+1);
  return dp[r-l+1][T];
}

int diskset(){
  int copy[I];
  int i = 0, v = 0;
  while (i!=I){
    copy[i] = value[i];
    i++;
  }
  sort(copy,copy+I);
  for (int j = 0; j < M && j < I; ++j)
    v+=copy[I-j-1];

  return v;
}

void getsets(int l, int r){
  if (l > r) return;
  
  //= debug  
  // for (int i = 0; i < N; ++i)
  //   if (l <= i && i <= r)
  //     cout << songs[i] << " ";
  //   else
  //     cout << "_ ";
  // cout << endl;
  //= debug
  
  value[I++] = evaluate(l,r);
  
  getsets(0,l-1);
  
  if (l == 0){
    // cout << "end:"  << I << endl;
    max_songs = max(max_songs,diskset());
    I--;
  }
  
  getsets(l+1,r); 
  
  if (l == 0){
    // cout << "end:"  << I << endl;
    I--;
  }

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

  getsets(0,N-1);
  fout << max_songs << endl;

  fout.close();
  return 0;
}
