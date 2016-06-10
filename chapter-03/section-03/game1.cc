/*
ID: min_j
LANG: C++
TASK: game1
Date: 09/06/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#define MAXN 1201
#define max(a,b) (a) < (b) ? b : a
using namespace std;
int N;
int board[MAXN];
int player[2];

int solve(int p,int l, int r){
  if (l == r)
    return board[l];
  int moveL = board[l]+solve((p+1)%2,l+1,r);
  int moveR = board[r]+solve((p+1)%2,l,r-1);
  if (moveL > moveR){
    player[p] = max(moveL,player[p]);
    return moveL;
  }
  else {
    player[p] = max(moveR,player[p]);
    return moveR;
  }
}

int main(){
  ifstream fin("game1.in");
  ofstream fout("game1.out");
  fin>>N;

  
  for (int i = 1; i <= N; ++i)
    fin>>board[i];
  cout << solve(0,1,N) << endl;
  cout << player[0] << endl;
  cout << player[1] << endl;

  return 0;
}


