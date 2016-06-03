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
#include <climits>
#include <cassert>
using namespace std;
#define DEBUG
#define infinity INT_MAX
#define MROW 30
#define MCOL 26
int R,C;
struct coord {
  int r,c,d;
  coord(int row,int col, int dist){
    r = row; c = col; d = dist;
  };
  bool operator<(const coord& rhs) const{
    return d < rhs.d;
  }
};
char piece[MROW][MCOL];
int boards[MROW*MCOL][MROW][MCOL];
int K,Krow[MROW],Kcol[MCOL];

bool valid(int (*board)[MCOL], int r, int c, int step){
  if (r < 0 || r >= R || c < 0 || c >= C ||
      board[r][c] < step)
    return false;
  return true;
}

void bfs_from(int (*board)[MCOL], int r, int c){
  priority_queue<coord> Q;
  int step = 0,cr,cc;
  board[r][c] = step;
  Q.push(coord(r,c,step));
  while(!Q.empty()){
    coord cur = Q.top(); Q.pop();
    step = cur.d + 1;
    cr = cur.r-1; cc = cur.c+2;
    if (valid(board,cr,cc,step)){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r-1; cc = cur.c-2;    
    if (valid(board,cr,cc,step)){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r+1; cc = cur.c+2;    
    if (valid(board,cr,cc,step)){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r+1; cc = cur.c-2;    
    if (valid(board,cr,cc,step)){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r+2; cc = cur.c-1;    
    if (valid(board,cr,cc,step)){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r-2; cc = cur.c-1;    
    if (valid(board,cr,cc,step)){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r+2; cc = cur.c+1;    
    if (valid(board,cr,cc,step)){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r-2; cc = cur.c+1;    
    if (valid(board,cr,cc,step)){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    step++;
  }

}

void reset(int (*board)[MCOL]){
  for (int i = 0; i < R*C; ++i)
    board[i/C][i%C] = infinity;
}
#ifdef DEBUG
void debugprint(int (*board)[MCOL]){
  cout << endl;
  cout << "  ";
  for (int i = 0; i < C; ++i)
    cout << (char) ('A'+i) << "\t";
  cout << endl;
  for (int i = 0; i < R; ++i){
    cout << i+1 << ' ';
    for (int j = 0 ; j < C; ++j){
      if (board[i][j] != infinity)
        cout << board[i][j] << "\t";
      else
        cout << '-' << '\t';
    }
    cout << endl;
  }
}
#endif

int main(){
  ifstream fin("camelot.in");
  ofstream fout("camelot.out");
  assert(fin.is_open() && fout.is_open());
  fin>>R>>C;
  char col,row;
  fin>>col>>row;
  row -= '0'+1; col-='A';
  piece[row][col] = 'K';
  Krow[K] = row; Kcol[K] = col;
  K++;
  while (fin>>col>>row){
    row-='0'+1; col-='A';
    piece[row][col] = 'k';
    Krow[K] = row; Kcol[K] = col;
    K++;
  }
  fin.close();

  for (int i = 1; i < K; ++i){
    reset(boards[i]);
    bfs_from(boards[i],Krow[i],Kcol[i]);
  }

  int output[MROW][MCOL];
  for (int i = 0; i < R*C; ++i)
    output[i/C][i%C] = 0;
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j){
      for (int k = 1; k < K; ++k)
        output[i][j]+=boards[k][i][j];
    }

#ifdef DEBUG
  cout << "  ";
  for (int i = 0; i < C; ++i)
    cout << (char) ('A'+i) << " "; 
  cout << endl;
  for (int i = 0; i < R; ++i){
    cout << i+1 << ' ';
    for (int j = 0 ; j < C; ++j){
      if (piece[i][j] == 0)
        cout << '-' << ' ';
      else
        cout << piece[i][j] << ' ';
    }
    cout << endl;
  }

  for (int k = 0; k < K; ++k)
    debugprint(boards[k]);
  debugprint(output);
#endif
  
  fout.close();  
  return 0;
}

