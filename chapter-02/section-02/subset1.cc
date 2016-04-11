/*
ID: min_j
LANG: C++
TASK: subset
Date: 10/04/2015
Analysis:
We have the following recurrence relation

let f(i,j) be the numbers of ways to sum i given
set j. Then f(i,j) = f(i,j-1)+f(i-j,j-1).
Base case f(0,0) = 1;

We want the number of ways to get to N(N+1)/4 because
every partition of equal sum will equal that.

Note: Only sums of sets that are not odd have solutions

*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXN 39
#define INT long long
INT N;
INT memo[MAXN*(MAXN+1)/4 + 1][MAXN + 1];

INT f(INT i, INT j){
  if (i < 0 || j < 0)
    return 0;
  if (i == 0 && j == 0)
    return 1;
  if (memo[i][j] != -1)
    return memo[i][j];
  else
    return memo[i][j] = f(i,j-1) + f(i-j,j-1);
}

int main(){
  ifstream fin("subset.in");
  ofstream fout("subset.out");
  fin >> N;
  fin.close();

  int sum = N*(N+1)/2;
  for (int i = 0; i < MAXN*(MAXN+1)/4 + 1 ; ++i)
    for (int j = 0; j < MAXN + 1; ++j)
      memo[i][j] = -1;
  
  if (sum % 2 != 0)
    fout << 0 << endl;
  else
    fout << f(sum/2,N)/2 << endl;

  fout.close();
  return 0;
}
