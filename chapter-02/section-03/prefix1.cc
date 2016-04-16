/*
ID: min_j
LANG: C++
TASK: prefix
Date: 15/04/2015
Anaylsis:
  Dynamic programming ftw.
  We build up a 1 dimensional dp array since
  we don't need to know what the longest primitive
  constituant is composed of. Only the length.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define MAXL 201
#define MAXP 11
#define MAXS 200001
string prim[MAXL];
string seq = " ";
int L, K;
int dp[MAXS];

int main(){
  ifstream fin("prefix.in");
  ofstream fout("prefix.out");
  string s;
  while (fin >> s)
    if (s == ".")
      break;
    else 
      prim[++L] = s;
  while (fin >> s)
    seq+=s;
  prim[0] = "";

  dp[0] = 1;
  for (int i = 0; i < seq.size(); ++i)
    if (dp[i])
      for (int j = 1; j <= L; ++j)
        if (seq.compare(i+1, prim[j].size(), prim[j]) == 0)
          dp[i+prim[j].size()] = 1;
  
  int sol = 0;
  for (sol = seq.size()-1; sol > 0; --sol)
    if (dp[sol]){
      break;
    }
  fout << sol << endl;

  return 0;
}
