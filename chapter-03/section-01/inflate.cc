/*
ID: min_j
LANG: C++
TASK: inflate
Date: 07/05/2015
Anaylsis:
  I think we use dynamic programming to solve this
  problem
*/
#include <iostream>
#include <fstream>
using namespace std;
#define DEBUG
#define MAX 10001

int M,N;
struct cate{
  int m,p;
};
cate pc[MAX];
int dp[MAX][MAX];
int main(){
  ifstream fin("inflate.in");
  ofstream fout("inflate.out");
  fin>>M>>N;
  for (int i = 0; i < N; ++i){
    fin>>pc[i].p;
    fin>>pc[i].m;
  }
  for (int m = 0; m < M; ++m){
    for (int p = 0; p < N; ++p){
      dp[pc[p].m] += pc[p].p;
    }
  }

#ifdef DEBUG
  for (int i = 0; i < M; ++i){
    for (int j = 0; j < N; ++j)
      cout<<dp[i][j]<<" ";
    cout<<endl;
  }
#endif
    
    
  return 0;
}
