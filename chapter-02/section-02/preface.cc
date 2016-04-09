/*
ID: min_j
LANG: C++
TASK: preface
Date: 07/04/2015
Analysis:
*/
#include <iostream>
#include <fstream>
using namespace std;
int N;

void roman(char *s, int n){
  while(n){
    if (n - 1000 > 0){
      sprintf(s, "%sM", s);
      n -= 1000;
    }
    else if (n - 500 > 0){
      sprintf(s, "%sD", s);
      n -= 500;
    }
    else if (n - 100 > 0){
      sprintf(s, "%sC", s);
      n -= 100;
    }
    else if (n - 50 > 0){
      sprintf(s, "%sL", s);
      n -= 50;
    }
    else if (n - 10 > 0){
      sprintf(s, "%sX", s);
      n -= 10;
    }
    else if (n - 5 > 0){
      sprintf(s, "%sV", s);
      n -= 5;
    }
    else{
      sprintf(s, "%sI", s);
      n -= 1;
    }
  }
}

int main(){
  ifstream fin("preface.in");
  ofstream fout("preface.out");
  fin>>N;
  fin.close();

  char buf[100];
  roman(buf, 268);
  printf("%s\n", buf);
  
  fout.close();
  return 0;
}
