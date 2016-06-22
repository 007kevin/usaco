/*
ID: min_j
LANG: C++
TASK: rockers
Date: 21/06/2016
Anaylsis:
  If you think about it, once songs are selected to be 
  included in a disk, their song order will not matter. 
  Also, disk order will not matter as well. This means
  we can perform 0/1 knapsack per disk as long as we
  mark off the 'range' of songs that were selected.
  Most likely, previous runs of 0/1 knapsack will partition
  the N songs, therefore for the current disk, we must
  select the partition that gives us the highest value
  and continue for the next disk.
*/
#include <iostream>
#include <fstream>
#include <cassert>
#define MAXN 20
#define MAXT 21
#define MAXM 20
using namespace std;
int N,T,M;
int songs[MAXN];
int chosen[MAXN];
int dp[MAXM][MAXT];

int main(){
  ifstream fin("rockers.in");
  ofstream fout("rockers.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>T>>M;
  for (int i = 0; i < N; ++i)
    fin>>songs[i];
  for (int i = 0; i < M; ++i){
    for (int j = 1; j <= T; ++j){
      for (int k = 
    }
  }
    
    
  
  return 0;
}
