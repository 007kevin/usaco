/*
ID: min_j
LANG: C++
TASK: fracdec
Date: 04/05/2015
Anaylsis:
*/
#include <iostream>
#include <fstream>
using namespace std;
int N,D;
void convert(char *buf, int n, int d){
  
  
}

int main(){
  ifstream fin("fracdec.in");
  ofstream fout("fracdec.out");
  fin>>N>>D;
  fin.close();
  char buf[10000];
  convert(buf,N,D);


  fout.close();
  return 0;
}
