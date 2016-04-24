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


int main(){
  ifstream fin("concom.in");
  ofstream fout("concom.out");
  fin>>N;
  int a,b;
  for (int i = 0; i < N; ++i){
    fin>>a>>b;
    fin>>graph[a][b];
  }
  
  for (int i = 1; i <= 100; ++i)
    for (int j = 1; j <= 100; ++j){
      if (i != j && graph[i][j] > 50)
        cout << i << " " << j << endl;
    }
  
}
    

