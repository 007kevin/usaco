/*
ID: min_j
LANG: C++
TASK: subset
Date: 11/04/2015
Anaylsis:
Redoing the subset sum problem to learn 0/1 knapsack
dynamic programming
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXN 39
int N;
long int bucket[MAXN+1][MAXN*(MAXN+1)/4 + 1];

int main(){
  ifstream fin("subset.in");
  ofstream fout("subset.out");
  fin >> N;
  bucket[0][0] = 1;
  for (int i = 1; i <= N; ++i){
    bucket[i][0] = 1;
    for (int j = 0; j <= N*(N+1)/4; ++j){
      bucket[i][i+j] += bucket[i-1][j];
    }
  }
  for (int i = 0; i <= N; ++i){
    cout << i << "::  ";
    for (int j = 0; j <= N*(N+1)/4; ++j)
      cout << bucket[i][j] << " ";
    cout << endl;
  }
  return 0;
}
