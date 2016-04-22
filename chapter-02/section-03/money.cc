/*
ID: min_j
LANG: C++
TASK: money
Date: 22/04/2015
Anaylsis:

*/
#include <iostream>
#include <fstream>
#include <vector>
#define MAXV 26
#define MAXN 10001
using namespace std;
int V, N;
int dp[MAXN][MAXV], coin[MAXV];

void solve(){
  for (int i = 0; i < N; ++i)
    for (int j = 0; j <= V; ++j)
      if (dp[i][j]){
        for (int c = 1; c <= V; ++c){
          if (j <= c)
            dp[i+coin[c]][c] += dp[i][j];
        }
      }
}

int main(){
  ifstream fin("money.in");
  ofstream fout("money.out");
  fin>>V>>N;
  for (int i = 1; i <= V; ++i)
    fin >> coin[i];
  dp[0][0] = 1;
  solve();
  // for (int i = 0; i <= N; ++i){
  //   for (int j = 0; j <= V; ++j)
  //     cout << dp[i][j] << " ";
  //   cout << endl;
  // }

  int sum = 0;
  for (int i = 1; i <= V; ++i)
    sum+=dp[N][i];
  fout << sum << endl;
  fout.close();
}
