/*
ID: min_j
LANG: C++
TASK: nuggets
Date: 05/07/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <queue>
#define max(a,b) ((a) > (b) ? a : b)
using namespace std;
int N;
int P[10];
int main(){
  ifstream fin("nuggets.in");
  ofstream fout("nuggets.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N;
  for (int i = 0; i < N; ++i)
    fin>>P[i];
  sort(P,P+N);
  int maxP = P[N-1];
  int modP[maxP];
  int count = 0;
  int max_impossible = 0;
  memset(modP,0,sizeof(modP));
  queue<int> Q;
  Q.push(0);
  while(!Q.empty()){
    int n = Q.front(); Q.pop();
    if (modP[n%maxP] == 0){
      modP[n%maxP] = 1;
      count++;
      if (count == maxP) break;
      if (n > max_impossible){
        for (int i = 0; n-i >= 0 && i < maxP; ++i){
          if (modP[(n-i)%maxP] == 0){
            max_impossible = n-i;
            break;
          }
        }
      }
      for (int i = 0; i < N; ++i)
        Q.push(n+P[i]);
    }
  }
  if (count != maxP)
    fout << 0 << endl;
  else
    fout << max_impossible << endl;
  fin.close();
  
  fout.close();
  return 0;
}
