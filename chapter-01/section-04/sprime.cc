/*
ID: min_j
LANG: C++
TASK: sprime
Date: 25/03/2015
Comment:
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
//#define MAXN 100000000

ifstream fin("sprime.in");
ofstream fout("sprime.out");

//unsigned long prime[MAXN];
char spr[10];
int N;

bool isprime(unsigned long n){
  //  if (prime[n]) return true;
  
  if (n == 2)
    return true;
  if (n == 3)
    return true;
  if (n % 2 == 0)
    return false;
  if (n % 3 == 0)
    return false;
  int i = 5;
  int w = 2;
  while (i * i <= n){
    if (n % i == 0)
      return false;
    i+=w;
    w = 6 - w;
  }
  //  prime[n] = 1;
  return true;
}

void generate_spr(int si){
  if (si == N){
    spr[si] = '\0';
    unsigned long num = strtol(spr, NULL, 0);
    fout << num << endl;
    return;
  }
  for (int i = si == 0 ? 2 : 1; i <= 9; ++i){
    spr[si] = i+'0';
    spr[si+1] = '\0';
    if (isprime(strtol(spr, NULL, 0)))
      generate_spr(si+1);
  }
  
}

int main(){
  fin>>N;
  fin.close();
  generate_spr(0);
  fout.close();
  return 0;
}
