/*
ID: min_j
LANG: C++
TASK: ariprog
Date: 15/03/2015
Comment: 
Solution correct, but too slow to meet judgement requirements.
Big O?
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;
#define MAXN 25
int N,M, MAXBS;
int seq[MAXN];
int BS[625001];

struct ans{
  int s,d;
};
ans answers[10000];
int ai;

bool compare(ans a, ans b){
  return a.d < b.d;
}

bool isbisquare(int n){
  if (BS[n] == 0){
    for (int i = 0; i <= M; ++i)
      for (int j = 0; j <= M; ++j)
        if (pow(i,2) + pow(j,2) == n){
          BS[n] = 1;
          return true;
        }
    return false;
  }
  else
    return true;
}

void generate_seq(int a, int b, int n){
  if (n == N){
    for (int i = 0; i < N; ++i)
      cout << seq[i] << " ";
    cout << endl;
    answers[ai].s = seq[0]; 
    answers[ai].d = b;
    ai++;
    return;
  }
  seq[n] = a + (n*b);
  if (isbisquare(seq[n])){
    generate_seq(a, b, n+1);
  }
  else
    return;
}

void solve(){
  int a = 0, b = 1;
  while (a <= MAXBS){
    b = 1;
    while (b <= MAXBS)
      generate_seq(a, b++, 0);
    a++;
  }
  sort(answers, answers + ai, compare);
}

int main(void){
  ifstream fin("ariprog.in");
  ofstream fout("ariprog.out");
  fin >> N >> M;
  MAXBS = 2*pow(M,2); // We keep printing answers until we reach the maximum bisquare
  fin.close();
  solve();
  
  if (ai == 0)
    fout << "NONE" << endl;
  else
    for (int i = 0; i < ai; i++)
      fout << answers[i].s << " " << answers[i].d << endl;
  
  fout.close();
  return 0; 
}
