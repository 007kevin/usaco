/*
ID: min_j
LANG: C++
TASK: concom
Date: 23/04/2015
Anaylsis:

*/
#include <iostream>
#include <fstream>
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
  
}
    

