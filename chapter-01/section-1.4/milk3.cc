/*
ID: min_j
LANG: C++
TASK: milk3
Date: 15/03/2015
Comment:
state array to hold state of tested milk amounts to
prevent stack overflow.
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXA 21 // Max values C can have
#define MAXS 202021 // Most state the buckets can have
#define ST(X, Y, Z) (((X) * 10000) + ((Y) * 100) + (Z))

int A,B,C;
int ans[MAXA];
int state[MAXS];
int count;
void solve(int a, int b, int c){
  //  cout << a << b << c << endl;
  if (a == 0) ans[c] = 1;
  if (state[ST(a,b,c)] == 0){
      return;
  }
  
  if (a){
    int na, nb, nc;
    na = a < B-b ? 0 : a-(B-b);
    nb = a < B-b ? b+a : B;
    nc = c;
    if (state[ST(na,nb,nc)] == 0){
      state[ST(na,nb,nc)] = 1;
      solve(na, nb, nc);
    }


    na = a < C-c ? 0 : a-(C-c);
    nb = b;
    nc = a < C-c ? c+a : C;
    if (state[ST(na,nb,nc)] == 0){
      state[ST(na,nb,nc)] = 1;      
      solve(na ,nb, nc);
    }

  }
  if (b){
    int na, nb, nc;
    na = b < A-a ? a+b : A;
    nb = b < A-a ? 0 : b-(A-a);
    nc = c;
    if (state[ST(na,nb,nc)] == 0){
      state[ST(na,nb,nc)] = 1;      
      solve(na, nb, nc);
    }

    na = a;
    nb = b < C-c ? 0 : b-(C-c);
    nc = b < C-c ? c+b : C;
    if (state[ST(na,nb,nc)] == 0){
      state[ST(na,nb,nc)] = 1;
      solve(na, nb, nc);
    }

  }
  if (c){
    int na, nb, nc;
    na = c < A-a ? a+c : A;
    nb = b;
    nc = c < A-a ? 0 : c-(A-a);
    if (state[ST(na,nb,nc)] == 0){
      state[ST(na,nb,nc)] = 1;      
      solve(na, nb, nc);
    }


    na = a;
    nb = c < B-b ? b+c : B;
    nc = c < B-b ? 0 : c-(B-b);
    if (state[ST(na,nb,nc)] == 0){
      state[ST(na,nb,nc)] = 1;      
      solve(na, nb, nc);
    }
  }
}

int main(){
  ifstream fin("milk3.in");
  ofstream fout("milk3.out");
  fin>>A>>B>>C;
  fin.close();
  state[C] = 1; // Set initial state
  solve(0, 0, C);
  for (int i = 0; i <  MAXA; ++i)
    if (ans[i]) fout << i << (i == C ? '\n' : ' ');
  fout.close();
  return 0;
}
