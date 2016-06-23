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
  if (s > e || m == M)
    return 0;
  int dp[e-s+2][T+1];
  int L,R;
  for (int i = 0; i <= T; ++i) dp[0][i] = 0;
  for (int i = 0; i <= e-s+1; ++i) dp[i][0] = 0;
  
  for (int i = 1; i <= e-s+1; ++i)
    for (int j = 1; j <= T; ++j){
      if (songs[i+s-1] > j)
        dp[i][j] = dp[i-1][j];
      else{
        if (dp[i-1][j] <= dp[i-1][j-songs[i+s-1]] + 1){
          dp[i][j] = dp[i-1][j-songs[i+s-1]] + 1;
          R = i+s-1;
        }
        else
          dp[i][j] = dp[i-1][j];
      }
    }
  // backtrack to find included items
  int i = e-s+1;
  L = i;
  int j = T;
  while (i > 0){
    if (dp[i][j] == 0) break;
    if (dp[i][j] == dp[i-1][j])
      i--;
    else{
      L = i+s-1;
      j -= songs[i+s-1];
      i--;
    }
  }
  // Reduce potential gap between included songs
  int item = songs[L];
  printf("%d\n",L);
  int r = R-dp[e-s+1][T]+1;
  while (songs[r] != item) r--;
  L = r;


  for (int i =0 ; i <= e-s+1; ++i){
    for (int j = 0; j <= T; ++j)
      printf("%d ", dp[i][j]);
    printf("\n");
  }
  printf("m:%d - %d %d (%d) item:%d\n", m, L,R, dp[e-s+1][T],item);
  return 0;
  
  return dp[e-s+1][T] + max(fill_disks(m+1,s,L-1),fill_disks(m+1,R+1,e));
}

int main(){
  ifstream fin("rockers.in");
  ofstream fout("rockers.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>T>>M;
  for (int i = 0; i < N; ++i)
    fin>>songs[i];
  for (int i = 0; i < N; ++i)
    printf("%d\t", songs[i]);
  printf("\n");
  for (int i = 0; i < N; ++i)
    printf("%d\t", i);
  printf("\n");  
  
  fout << fill_disks(0,0,N-1) << endl;
  return 0;
}
