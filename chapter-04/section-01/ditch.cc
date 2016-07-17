/*
ID: min_j
LANG: C++
TASK: ditch
Date: 15/07/2016
Anaylsis:
  This involves use of Network Flow Algorithms.
  Note: 
    - Each iteration of graph, we must find max flow path
    - After each iteration, we must add the reverse arc of
      the minimum arc along the path

  https://en.wikipedia.org/wiki/Ford-Fulkerson_algorithm
  It is good to note for finding the augmenting paths in 
  the residual network is not specified, therefore we could
  have also used BFS to find paths from sink to source. Because
  of USACO's mention of the algorithm finding the path
  with max cap, attempts to solve this problem may have been
  harder than it could have been.
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <climits>
#include <queue>
#define MAXN 201
#define MAXM 201
#define infinity INT_MAX
using namespace std;
int N,M,C;
int matrix[MAXM][MAXM];
int visited[MAXM];
int parent[MAXM];
int shortest[MAXM];
struct ditch {
  int m,d,p;
  ditch(int d_m,int dist, int parent){
    m = d_m;
    d = dist;
    p = parent;
  };
  bool operator<(const ditch& rhs) const {
    return d > rhs.d;
  }
};
int main(){
  ifstream fin("ditch.in");
  ofstream fout("ditch.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>M;
  int s,e,c;
  for (int i = 0; i < N; ++i){
    fin>>s>>e>>c;
    matrix[s][e]+=c;
  }
  fin.close();
  while (true){
    for (int i = 1; i <= M; ++i){
      visited[i] = 0;      
      parent[i] = 0;
      shortest[i] = infinity;
    }
    priority_queue<ditch> PQ;
    PQ.push(ditch(1,0,0));
    shortest[1] = 0;
    int ms,me,mc = infinity;
    while (!PQ.empty()){
      ditch m = PQ.top(); PQ.pop();
      // This may never trigger if graph has no loops. Without this with loops,
      // answer seems higher ? (therefore incorrect?).
      // In two runs with and without this statement, online judge deemed solution
      // correct except for test case 10, where first run with statement resulted in
      // lower score. Perhaps for SPA's, we need this extra visit check because
      // while a node was in PQ, it may have gotten visited.
      if (visited[m.m]) continue;
      visited[m.m] = 1;
      parent[m.m] = m.p;
      if (m.p != 0 && matrix[m.p][m.m] < mc){
        ms = m.p;
        me = m.m;
        mc = matrix[m.p][m.m];
      }
      for (int i = 1; i <= M; ++i)
        if (matrix[m.m][i] &&
            visited[i] == 0 && 
            shortest[m.m]+matrix[m.m][i] < shortest[i]){
          shortest[i] = shortest[m.m]+matrix[m.m][i];
          PQ.push(ditch(i,shortest[m.m]+matrix[m.m][i],m.m));
        }
    }
    if (parent[M] == 0)
      break;
    int cur = M;
    while (parent[cur] != 0){
      matrix[parent[cur]][cur]-=mc;
      matrix[cur][parent[cur]]+=mc; // Add reverse arc
      cur = parent[cur];
    }
    C+=mc;
  }
  fout << C << endl;
  fout.close();
  return 0;
}
