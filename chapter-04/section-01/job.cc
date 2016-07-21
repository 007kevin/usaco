/*
ID: min_j
LANG: C++
TASK: job
Date: 20/07/2016
Anaylsis:
  Ford-Fulkerson algorithm where capacity for 
  each machine is the number of jobs it can 
  process in time 't'. Keep incrementing t until
  max flow of network reaches N. Value of 't' is
  the min. amount of time to perform both operations
  on all N jobs. We will find earliest time operation "A"
  can be completed for all N jobs along the way.
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#define MAXM 61
#define MAXN 1001
using namespace std;
int N,M1,M2;
int P[MAXM];
// network-flow-algorithm will return true
// when time t allows processing of all jobs
bool nfa(int t){
  assert(t != 0);
  int M = M1+M2+2;
  int matrix[M][M];
  // setup matrix
  memset(matrix,0,sizeof(matrix));
  for (int i = 1; i <= M1; ++i)
    matrix[0][i] = t/P[i];
  for (int i = 1; i <= M1; ++i)
    for (int j = M1+1; j <= M1+M2; ++j)
      matrix[i][j] = t/P[j];
  for (int i = M1+1; i <= M1+M2; ++i)
    matrix[i][M1+M2+1] = MAXN;
  // run ford-fulkerson
  while (true){
    int cur = 0;
    while (cur!=M-1){
      int i = 0;
      
    }
  }

  return true;
}
int main(){
  ifstream fin("job.in");
  ofstream fout("job.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>M1>>M2;
  for (int i = 1; i <= M1+M2; ++i) fin>>P[i];
  fin.close();

  fout.close();
  return 0;
}
