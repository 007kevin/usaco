/*
ID: min_j
LANG: C++
TASK: concom
Date: 23/04/2015
Anaylsis:
  I copy the results of graph for company i to final and reset
  graph. This solution seemed harder than it was.
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int N;
int orig[101][101];
int graph[101][101];
int final[101][101];

void own(int a){
  for (int i = 1; i <= 100; ++i){
    if (graph[a][i] > 50 && graph[i][0] == 0){
      graph[i][0] = 1;
      own(i);
      for (int j = 1; j <= 100; ++j)
        graph[a][j] += graph[i][j];
      i = 0;
    }
  }
}

int main(){
  ifstream fin("concom.in");
  ofstream fout("concom.out");
  fin>>N;
  int a,b,c;
  for (int i = 0; i < N; ++i){
    fin>>a>>b>>c;
    orig[a][b]+=c;
    graph[a][b]+=c;
  }
  
  for (int i = 1; i <= 100; ++i){
    own(i);
    final[i][0] = 1;
    for(int j = 0; j <= 100; ++j)
      for (int k = 0; k <= 100; ++k){
        if (j == i && k > 0)
          final[j][k] = graph[j][k];
        graph[j][k] = orig[j][k];
      }
  }
  
  for (int i = 1; i <= 100; ++i)
    for (int j = 1; j <= 100; ++j){
      if (i != j && final[i][j] > 50)
        fout << i << " " << j << endl;
    }
}
    

