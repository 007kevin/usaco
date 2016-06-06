/*
ID: min_j
LANG: C++
TASK: camelot
Date: 01/06/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <climits>
#include <cassert>
using namespace std;
#define infinity INT_MAX
#define max(a,b) (a) < (b) ? b : a
#define MROW 30
#define MCOL 26
int R,C;
int mover[] = {-1,-1,+1,+1,+2,-2,+2,-2};
int movec[] = {+2,-2,+2,-2,-1,-1,+1,+1};
int K,Krow[MROW*MCOL],Kcol[MROW*MCOL]; // King is when K=0
int piece[MROW][MCOL];
int board[MROW][MCOL];
struct coord {
  int r,c,d;
  coord(int row,int col,int dist){
    r = row; c = col; d = dist;
  }
};

void reset(int (*board)[MCOL]){
  for (int i = 0; i < R*C; ++i)
    board[i/C][i%C] = infinity;
}

bool valid(int (*board)[MCOL], int r, int c){
  if (r < 0 || r >= R || c < 0 || c >= C)
    return false;
  return true;
}

int king_from(int r, int c){
  return max(abs(Krow[0]-r),abs(Kcol[0]-c));
}

int bfs_from(int (*board)[MCOL], int r, int c){
  reset(board);
  int knights = 0;
  int minking = king_from(r,c);
  queue<coord> Q;
  Q.push(coord(r,c,0));
  while(!Q.empty() && knights < K){
    coord cur = Q.front(); Q.pop();
    if (!valid(board,cur.r,cur.c) ||
        board[cur.r][cur.c] != infinity)
      continue;
    board[cur.r][cur.c] = cur.d;

    //Backtrack from found knight to initial
    //position to track the lowest king steps
    if (piece[cur.r][cur.c] == 1){
      int step = cur.d-1;
      int backtrack_r = cur.d;
      int backtrack_c = cur.c;
      while(board[backtrack_r][backtrack_c] != 0){
        x
      }
    }
    for (int i = 0; i < 8; ++i)
      Q.push(coord(cur.r+mover[i],cur.c+movec[i],cur.d+1));
  }
}

void debugprint(int (*board)[MCOL]){
  cout << endl;
  cout << "\t";
  for (int i = 0; i < C; ++i)
    cout << (char) ('A'+i) << "\t";
  cout << endl;
  for (int i = 0; i < R; ++i){
    cout << i+1 << '\t';
    for (int j = 0 ; j < C; ++j){
      if (board[i][j] != infinity)
        cout << board[i][j] << "\t";
      else
        cout << '-' << '\t';
    }
    cout << endl;
  }
}

int main(){
  ifstream fin("camelot.in");
  ofstream fout("camelot.out");
  assert(fin.is_open() && fout.is_open());
  fin>>R>>C;
  int row; char col;
  fin>>col>>row;
  row--; col-='A';
  piece[row][col] = 2;
  Krow[K] = row; Kcol[K] = col;
  K++;
  while (fin>>col>>row){
    row--; col-='A';
    piece[row][col] = 1;
    Krow[K] = row; Kcol[K] = col;
    K++;
  }
  fin.close();

  debugprint(piece);
  
  
  
  fout.close();  
  return 0;
}

