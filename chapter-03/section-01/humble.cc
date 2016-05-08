/*
ID: min_jn
LANG: C++
TASK: humble
Date: 07/05/2015
Anaylsis:
  Use a sorted queue to generate the numbers of S
  in increasing order.
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
#define MAXK 100
#define MAXN 300000
int S[MAXN+1];
int subS[MAXK+1];
int N,K;
int counter;

  

int main(){
  ifstream fin("humble.in");
  ofstream fout("humble.out");
  fin>>K>>N;
  for (int i = 0; i < K; ++i){
    fin>>subS[i];
    S[subS[i]] = 1;
  }
  for (int i = 0; true; ++i){
    if (S[i]){
      counter++;
      if (counter == N){
        fout << i << endl;
        break;
      }
      for (int j = 0; j < K; ++j)
        S[i*subS[j]] = 1;
    }
  }
  fout.close();
  return 0;
}
