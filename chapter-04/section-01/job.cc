/*
ID: min_j
LANG: C++
TASK: job
Date: 20/07/2016
Anaylsis:
  Ford-Fulkerson algorithm where capacity for 
  each machine is the number of jobs it can 
  process in time 't'. Keep incrementing t until
  max flow of network reaches >= N. Value of 't' is
  the min. amount of time to perform both operations
  on all N jobs. We will find earliest time operation "A"
  can be completed for all N jobs along the way.
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <climits>
#define MAXM 61
#define MAXN 1001
#define infinity INT_MAX
using namespace std;
int N,M1,M2;
int P[MAXM];
// network-flow-algorithm will return true
// when time t allows processing of all jobs
int nfa(int t){
  assert(t != 0);
  int M = M1+M2+2;
  int matrix[M][M];
  int flow = 0;
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
    int min_c = infinity;
    int v[M],p[M];
    for (int i = 0; i < M; ++i) v[i] = 0, p[i] = 0;
    while (cur!=M-1){
      v[cur] = 1;
      int i;
      for (i = 0; i < M; ++i)
        if (v[i] == 0 && matrix[cur][i]){
          if (matrix[cur][i] < min_c)
            min_c = matrix[cur][i];
          p[i] = cur;
          cur = i;
          break;
        }
      if (i == M) // Didn't find any more paths
        break;
    }
    if (cur!=M-1) // No more augmenting paths on residual network
      break;
    int rev = cur;
    while (rev != 0){
      matrix[p[rev]][rev]-=min_c;
      matrix[rev][p[rev]]+=min_c;
      rev = p[rev];
    }
    flow+=min_c;
  }
  return flow;
}
int nfa_A(int t){
  assert(t != 0);
  int M = M1+2;
  int matrix[M][M];
  int flow = 0;
  // setup matrix
  memset(matrix,0,sizeof(matrix));
  for (int i = 1; i <= M1; ++i)
    matrix[0][i] = t/P[i];
  for (int i = 1; i <= M1; ++i)
    matrix[i][M1+1] = MAXN;
  // run ford-fulkerson
  while (true){
    int cur = 0;
    int min_c = infinity;
    int v[M],p[M];
    for (int i = 0; i < M; ++i) v[i] = 0, p[i] = 0;
    while (cur!=M-1){
      v[cur] = 1;
      int i;
      for (i = 0; i < M; ++i)
        if (v[i] == 0 && matrix[cur][i]){
          if (matrix[cur][i] < min_c)
            min_c = matrix[cur][i];
          p[i] = cur;
          cur = i;
          break;
        }
      if (i == M) // Didn't find any more paths
        break;
    }
    if (cur!=M-1) // No more augmenting paths on residual network
      break;
    int rev = cur;
    while (rev != 0){
      matrix[p[rev]][rev]-=min_c;
      matrix[rev][p[rev]]+=min_c;
      rev = p[rev];
    }
    flow+=min_c;
  }
  return flow;
}

int nfa_B(int t){
  assert(t != 0);
  int M = M2+2;
  int matrix[M][M];
  int flow = 0;
  // setup matrix
  memset(matrix,0,sizeof(matrix));
  for (int i = 1; i <= M2; ++i)
    matrix[0][i] = t/P[M1+i];
  for (int i = 1; i <= M2; ++i)
    matrix[i][M2+1] = MAXN;
  // run ford-fulkerson
  while (true){
    int cur = 0;
    int min_c = infinity;
    int v[M],p[M];
    for (int i = 0; i < M; ++i) v[i] = 0, p[i] = 0;
    while (cur!=M-1){
      v[cur] = 1;
      int i;
      for (i = 0; i < M; ++i)
        if (v[i] == 0 && matrix[cur][i]){
          if (matrix[cur][i] < min_c)
            min_c = matrix[cur][i];
          p[i] = cur;
          cur = i;
          break;
        }
      if (i == M) // Didn't find any more paths
        break;
    }
    if (cur!=M-1) // No more augmenting paths on residual network
      break;
    int rev = cur;
    while (rev != 0){
      matrix[p[rev]][rev]-=min_c;
      matrix[rev][p[rev]]+=min_c;
      rev = p[rev];
    }
    flow+=min_c;
  }
  return flow;
}

int main(){
  ifstream fin("job.in");
  ofstream fout("job.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>M1>>M2;
  for (int i = 1; i <= M1+M2; ++i) fin>>P[i];
  fin.close();
  int t = 1;
  int output = nfa_A(3);
  int x;
  while((x = nfa_B(t)) < output)
    t++;
  cout << t << " seconds to process " << x << " items" << endl;

  fout.close();
  return 0;
}
