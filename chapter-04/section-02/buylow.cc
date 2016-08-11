/*
ID: min_j
LANG: C++
TASK: fence6
Date: 10/08/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstring>
#define max(a,b) ((a) < (b) ? b : a)
using namespace std;
int N;


int main(){
  ifstream fin("buylow.in");
  ofstream fout("buylow.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N;
  int dp[N+1][N+1];
  memset(dp,0,sizeof(dp));
  vector<int> days(N+1,0); // 1 based indexing
  for (int i = 1; i <= N; ++i)
    fin>>days[i];
  vector<int> sorted = days;
  
  
  return 0;
}

