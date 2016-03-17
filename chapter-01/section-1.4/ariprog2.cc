/*
ID: min_j
LANG: C++
TASK: ariprog
Date: 15/03/2015
Comment:
Working solutiion
*/
#include <iostream>
#include <fstream>
#include <algorithm>
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


void generate_seq(int a, int b, int n){
  
  if (a + (b*(N-1)) > MAXBS)
    return;

  if (n == N){
    // for (int i = 0; i < N; ++i)
    //   cout << seq[i] << " ";
    // cout << endl;
    
    answers[ai].s = seq[0]; 
    answers[ai].d = b;
    ai++;
  }
  
  seq[n] = a + n*b;
  if (BS[seq[n]] && n != N)
    generate_seq(a, b, n+1);
  else
    generate_seq(a, b+1, 0);
}

void solve(){
  MAXBS = 2*M*M;
  for (int i = 0; i <= M; ++i)
    for (int j = 0; j <= M; ++j)
      BS[i*i + j*j] = 1;

  for (int i = 0; i <= MAXBS; ++i)
    if (BS[i])
      generate_seq(i, 1, 0);

  sort(answers, answers + ai, compare);
}

int main(void){
  ifstream fin("ariprog.in");
  ofstream fout("ariprog.out");
  fin >> N >> M;

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
