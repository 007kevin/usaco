/*
ID: min_j
LANG: C++
TASK: prefix
Date: 15/04/2015
Anaylsis:
  This solution is O(N*L) where N is the number of constituants
  in the seqence. Too slow. 
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define MAXL 201
#define MAXP 11
#define MAXS 200001
string prim[MAXL];
string seq;
int L, K;

void solve(int cur){
  if (cur > K)
    K = cur;
  for (int i = 0; i < L; ++i){
    int j;
    for (j = 0; j < prim[i].size(); ++j)
      if (cur+j > seq.size() || prim[i][j] != seq[cur+j]){
        j = 0;
        break;
      }
    if (j)
      solve(cur+j);
  }
}

int main(){
  ifstream fin("prefix.in");
  ofstream fout("prefix.out");
  string s;
  while (fin >> s)
    if (s == ".")
      break;
    else 
      prim[L++] = s;
  while (fin >> s)
    seq+=s;

  solve(0);

  fout << K << endl;
  // for (int i = 0; i < L; ++i)
  //   cout << prim[i] << " ";
  // cout << endl;
  // cout << seq << endl;
  return 0;
}
