/*
ID: min_j
LANG: C++
TASK: agrinet
Date: 06/05/2015
Anaylsis:
  We use prim's algorithm to go through
  each farm and adding the minimum distance 
  to the spanning tree. We want to check every
  edge going out of the spanning tree to find the 
  minimum edge. We then add the edge to the cost
  and add the farm to the minimum spanning tree.
*/
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
#define MAXN 101
#define inf INT_MAX
int N;
int matrix[MAXN][MAXN];
int farms[MAXN];
int main(){
  ifstream fin("agrinet.in");
  ofstream fout("agrinet.out");
  fin>>N;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      fin>>matrix[i][j];
  fin.close();
  int cost = 0;
  farms[0] = 1;
  while (true){
    int min=inf;
    int minfarm;
    for (int i = 0; i < N; ++i)
      if (farms[i] == 1) // We found a farm that is included
        for (int j = 0; j < N; ++j)
          if (farms[j] == 0 && matrix[i][j] < min){ // Look for min farm from spanning tree
            min = matrix[i][j];
            minfarm = j;
          }
    if (min == inf)
      break;
    farms[minfarm] = 1;
    cost+=min;
  }
  fout<<cost<<endl;
  fout.close();
  
  return 0;
}
