/*
ID: min_j
LANG: C++
TASK: buylow
Date: 10/08/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
#include <cstring>
#define max(a,b) ((a) < (b) ? b : a)
using namespace std;
int N;
int dp[5001][5001];
int sequence[5001];

void parse(int I, int i, int j, set<vector<int> > &S, vector<int> days){
  if (dp[i][j] == 0){
    S.insert(vector<int>(sequence, sequence+I));
    return;
  }
  int ti = i;
  int tj = j;
  while (dp[ti][tj] == dp[i][j])
    ti--;
  while (dp[ti+1][tj] == dp[i][j])
    tj--;
  sequence[I] = days[ti+1];
  parse(I+1,ti,tj,S,days);
  ti = i;
  tj = j;
  while (dp[ti][tj] == dp[i][j])
    tj--;
  while (dp[ti][tj+1] == dp[i][j])
    ti--;
  sequence[I] = days[ti+1];  
  parse(I+1,ti,tj,S,days);
}

int main(){
  ifstream fin("buylow.in");
  ofstream fout("buylow.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N;
  vector<int> days(N+1,0); // 1 based indexing
  for (int i = 1; i <= N; ++i)
    fin>>days[i];
  vector<int> sorted = days;
  sort(sorted.begin(), sorted.end(),greater<int>());
  sorted.erase(unique(sorted.begin(),sorted.end()),sorted.end());
  // Find lowest common subsequence
  for (int i = 1; i < days.size(); ++i)
    for (int j = 1; j < sorted.size(); ++j)
      if (days[i] == sorted[j])
        dp[i][j] = dp[i-1][j-1]+1;
      else
        dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
  set<vector<int> > S;
  //parse(0,days.size()-1,sorted.size()-1,S,days);
  // for (int i = 0; i < days.size(); ++i){
  //   cout << days[i] << "\t";
  //   for (int j = 0; j < sorted.size(); ++j)
  //     cout << dp[i][j] << " ";
  //   cout << endl;
  // }
  
  fout << dp[days.size()-1][sorted.size()-1] << " " << S.size() << endl;
  
  return 0;
}

