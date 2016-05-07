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
#define MAX 10001

int M,N;
int pc[MAX];
int dp[MAX][MAX];
int main(){
  ifstream fin("inflate.in");
  ofstream fout("inflate.out");
  fin>>M>>N;
  int point;
  for (int i = 0; i < N; ++i){
    fin>>point;
    fin>>pc[point]
  }
  
    
    
  return 0;
}
