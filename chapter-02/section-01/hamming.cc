/*
ID: min_j
LANG: C++
TASK: hamming
Date: 02/06/2015
Analysis:
Key point in solving this problem was the following: 

"In the case of multiple solutions, your program should output 
the solution which, if interpreted as a base 2^B integer, would 
have the least value."

meaning we only take codewords that are less than the codeword 
to be replaced (line 63. approach similar to health holsteins prob.
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
using namespace std;

#define MAXN 64
#define MAXB 8
#define MAXD 7
int N,B,D;
int idx, codewords[MAXN];
ifstream fin("hamming.in");
ofstream fout("hamming.out");

int hamming(int a, int b){
  int c = a^b;
  int d = 0;
  while(c){
    d++;
    c &= c - 1; // strip off lowest bitset
  }
  return d;
}

int valid(int a){
  for (int i = 0; i < idx; ++i)
    if (hamming(codewords[i], a) < D)
      return 0;
  return 1;
}

void solve(){
  if (idx == N){
    int i;
    for (i = 0; i < idx - 1; ++i){
      fout << codewords[i];
      if (i!=0 && i%10 == 9)
        fout << endl;
      else
        fout << " ";
    }
    if (i%10 == 0)
      fout << endl;
    fout << codewords[i] << endl;;
  }
  for (int i = 0; i < (int) pow(2,B); ++i)
    if (i < codewords[idx] && valid(i)){
      codewords[idx++] = i;
      solve();
      idx--;
    }
}

int main(){
  fin>>N>>B>>D;
  fin.close();
  
  // initialize codewords
  int initval = (int) pow(2,B);
  for (int i = 0; i < N; ++i)
    codewords[i] = initval;

  solve();
  
  return 0;
}
