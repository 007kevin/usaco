/*
ID: min_j
LANG: C++
TASK: subset
Date: 11/04/2015
Anaylsis:
Redoing the subset sum problem to learn 0/1 knapsack
dynamic programming
 
Very nice solution by Nick Tomitov of Bulgaria:

#include <fstream>
using namespace std;
const unsigned int MAX_SUM = 1024;
int n;
unsigned long long int dyn[MAX_SUM];
ifstream fin ("subset.in");
ofstream fout ("subset.out");

int main() {
    fin >> n;
    fin.close();
    int s = n*(n+1);
    if (s % 4) {
        fout << 0 << endl;
        fout.close ();
        return ;
    }
    s /= 4;
    int i, j;
    dyn [0] = 1;
    for (i = 1; i <= n; i++)
        for (j = s; j >= i; j--) 
            dyn[j] += dyn[j-i];
    fout << (dyn[s]/2) << endl;
    fout.close();
    return 0;
}

*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXN 39
int N;
unsigned long long int bucket[MAXN+1][MAXN*(MAXN+1)/4 + 1];

int main(){
  ifstream fin("subset.in");
  ofstream fout("subset.out");
  fin >> N;
  bucket[0][0] = 1;
  long int sum = N*(N+1)/2;
  
  if (sum%2 != 0){
    fout << 0 << endl;
    return 0;
  }
  sum /= 2;
  for (int i = 1; i <= N; ++i){
    for (int j = 0; j <= sum; ++j){
      bucket[i][j] += bucket[i-1][j];
      if (j+i <= sum)
      bucket[i][j+i] += bucket[i-1][j];
    }
  }
  // for (int i = 0; i <= N; ++i){
  //   cout << i << "::  ";
  //   for (int j = 0; j <= N*(N+1)/4; ++j)
  //     cout << bucket[i][j] << " ";
  //   cout << endl;
  // }
  fout << bucket[N][sum]/2 << endl;
  return 0;
}
