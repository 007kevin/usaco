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

  Correction: This approach is wrong. Performing 0/1 knapsack
              per disk will fail for the following test case:

                  9 15 4 
                  15 7 8 6 9 5 10 4 11

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
int dp[MAXM][MAXN][MAXT];

int max(int a, int b){
  return a < b ? b : a;
}
  
int fill_disks(int m, int s, int e){
  if (s > e || m >= M)
    return 0;
  if (s == e){
    return songs[s] <= T ? 1 : 0;
  }
  int dp[e-s+2][T+1];
  for (int i = 0; i <= T; ++i) dp[0][i] = 0;
  for (int i = 0; i <= e-s+1; ++i) dp[i][0] = 0;
  
  for (int i = 1; i <= e-s+1; ++i)
    for (int j = 1; j <= T; ++j){
      if (songs[i+s-1] > j)
        dp[i][j] = dp[i-1][j];
      else
        dp[i][j] = max(dp[i-1][j],dp[i-1][j-songs[i+s-1]] + 1);
    }
  // backtrack to find included items
  int i = e-s+1;
  int j = T;
  int items[e-s+2], idx = 0;
  while (i > 0){
    if (dp[i][j] == 0) break;
    if (dp[i][j] == dp[i-1][j])
      i--;
    else{
      items[idx++] = i+s-1;
      j -= songs[i+s-1];
      i--;
    }
  }
  int L = items[0];
  int R = items[0];
  // Find the smallest range of songs that make up the disk
  for (int I = 0; I < idx; ++I){
    while (songs[items[I]] != songs[L]) L--;
  }
  printf("items: %d from %d to %d\n",dp[e-s+1][T],L,R);
  return dp[e-s+1][T] + fill_disks(m+1,s,L-1) + fill_disks(m+2,R+1,e);
}

int main(){
  ifstream fin("rockers.in");
  ofstream fout("rockers.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>T>>M;
  for (int i = 0; i < N; ++i)
    fin>>songs[i];
  // for (int i = 0; i < N; ++i)
  //   printf("%d\t", songs[i]);
  // printf("\n");
  // for (int i = 0; i < N; ++i)
  //   printf("%d\t", i);
  // printf("\n");  
  
  fout << fill_disks(0,0,N-1) << endl;
  return 0;
}
