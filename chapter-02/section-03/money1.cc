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
#define MAXN 10001
#define MAXV 26
using namespace std;
int V, N, coin[MAXV];
long long dp[MAXN];

void solve(){
  for (int v = 0; v < V; ++v)
    for (int n = 0; n <= N; ++n)
      if (coin[v]+n <= N)
        dp[n+coin[v]] += dp[n];
}

int main(){
  ifstream fin("money.in");
  ofstream fout("money.out");
  fin>>V>>N;
  for (int i = 0; i < V; ++i)
    fin >> coin[i];
  dp[0] = 1;
  solve();
  fout << dp[N] << endl;
  fout.close();
}
