/*
ID: min_j
LANG: C++
TASK: concom
Date: 23/04/2015
Anaylsis:

*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int N;
int graph[101][101];

void own(int a){
  for (int i = 1; i <= 100; ++i){
    if (graph[a][i] > 50 && graph[i][0] == 0){
      graph[i][0] = 1;
      own(i);
      for (int j = 1; j <= 100; ++j)
        graph[a][j] += graph[i][j];
      i = 1;
    }
  }
}

int main(){
  ifstream fin("concom.in");
  ofstream fout("concom.out");
  fin>>N;
  int a,b;
  for (int i = 0; i < N; ++i){
    fin>>a>>b;
    fin>>graph[a][b];
  }
  
  // //Debug
  // for (int i = 1; i <= 100; ++i){
  //   for (int j = 1; j <= 100; ++j){
  //     string space = " ";
  //     if (graph[i][j] < 10)
  //       space+=" ";
  //     cout << graph[i][j] << space;
  //   }
  //   cout << endl;
  // }
  
  for (int i = 1; i <= 100; ++i){
    own(i);
  }

  for (int i = 1; i <= 100; ++i)
    for (int j = 1; j <= 100; ++j){
      if (i != j && graph[i][j] > 50)
        fout << i << " " << j << endl;
    }

}
    

