/*
ID: min_j
LANG: C++
TASK: numtri
Date: 20/03/2015
Comment:
No need for fancy recusive solution.
Can just implement for loop to get max sum at each level
since we don't need what the path looks like.
*/
#include <iostream>
#include <fstream>
using namespace std;
int R, maxsum;
int ntree[1000][1000];
int memo[1000][1000];

void solve(){
  memo[0][0] = ntree[0][0];
  for (int i = 0; i < R - 1; ++i)
    for (int j = 0; j <= i; ++j){
      if (memo[i+1][j] < memo[i][j] + ntree[i+1][j])
        memo[i+1][j] = memo[i][j] + ntree[i+1][j];
      if (memo[i+1][j+1] < memo[i][j] + ntree[i+1][j+1])
        memo[i+1][j+1] = memo[i][j] + ntree[i+1][j+1];
    }

  // for (int i = 0; i < R; ++i){
  //   for (int j = 0; j <= i; ++j){
  //     cout << memo[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  for (int i = 0; i < R; ++i)
    if (maxsum < memo[R-1][i])
      maxsum = memo[R-1][i];
}


int main(){
  ifstream fin("numtri.in");
  ofstream fout("numtri.out");
  fin >> R;
  for (int i = 0 ; i < R; ++i)
    for (int j = 0; j <= i; ++j)
      fin >> ntree[i][j];
  fin.close();

  solve();
  fout << maxsum << endl;

  
  fout.close();
  return 0;
}
