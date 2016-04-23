/*
ID: min_j
LANG: C++
TASK: money
Date: 22/04/2015
Anaylsis:
  We want to use dp to get the number of combination
  of coins to get N. Since order of coins does not matter, we build
  up the dp table while ensuring not to double count coin 
  combinatio (i.e 1+2 = 3 = 2+1) . This is achieved by keeping the
  combinations of coins in sorted order ( j <= c ).
 
  For the solution, we sum up the values dp[N][].

*/
#include <iostream>
#include <fstream>
#include <vector>
#define MAXV 26
#define MAXN 10001
using namespace std;
int V, N, coin[MAXV];
long long dp[MAXN][MAXV];

void solve(){
  for (int i = 0; i < N; ++i)
    for (int j = 0; j <= V; ++j)
      if (dp[i][j]){
        for (int c = 1; c <= V; ++c){
          if (j <= c && i+coin[c] <= N)
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
  long long sum = 0;
  for (int i = 1; i <= V; ++i)
    sum+=dp[N][i];
  fout << sum << endl;
  fout.close();
}
