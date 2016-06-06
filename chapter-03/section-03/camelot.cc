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
#define DEBUG
#define infinity INT_MAX
#define MROW 30
#define MCOL 26
int R,C;
int mover[] = {-1,-1,+1,+1,+2,-2,+2,-2};
int movec[] = {+2,-2,+2,-2,-1,-1,+1,+1};
int kingr[] = {-1,-1,0,+1,+1,+1,0,-1};
int kingc[] = {0,+1,+1,+1,0,-1,-1,-1};

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
int K,Krow[MROW*MCOL],Kcol[MROW*MCOL]; // King is when K=0

bool valid(int (*board)[MCOL], int r, int c){
  if (r < 0 || r >= R || c < 0 || c >= C)
    return false;
  return true;
}

void bfs_from(int (*board)[MCOL], int r, int c){
  queue<coord> Q;
  Q.push(coord(r,c,0));
  while(!Q.empty()){
    coord cur = Q.front(); Q.pop();
    if (!valid(board,cur.r,cur.c) ||
        board[cur.r][cur.c] != infinity)
      continue;
    board[cur.r][cur.c] = cur.d;
    for (int i = 0; i < 8; ++i)
      Q.push(coord(cur.r+mover[i],cur.c+movec[i],cur.d+1));
  }
}

void bfs_king(int (*board)[MCOL], int r, int c){
  queue<coord> Q;
  Q.push(coord(r,c,0));
  while(!Q.empty()){
    coord cur = Q.front(); Q.pop();
    if (!valid(board,cur.r,cur.c) ||
        board[cur.r][cur.c] != infinity)
      continue;
    board[cur.r][cur.c] = cur.d;
    for (int i = 0; i < 8; ++i)
      Q.push(coord(cur.r+kingr[i],cur.c+kingc[i],cur.d+1));
  }
}

void reset(int (*board)[MCOL]){
  for (int i = 0; i < R*C; ++i)
    board[i/C][i%C] = infinity;
}

#ifdef DEBUG
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
#endif

int main(){
  ifstream fin("camelot.in.t");
  ofstream fout("camelot.out");
  assert(fin.is_open() && fout.is_open());
  fin>>R>>C;
  string col,row;
  int c,r;
  fin>>col>>row;
  r = atoi(row.c_str())-1; c = col[0]-'A';
  piece[r][c] = 'K';
  Krow[K] = r; Kcol[K] = c;
  K++;
  while (fin>>col>>row){
    r = atoi(row.c_str())-1; c = col[0]-'A';
    piece[r][c] = 'k';
    Krow[K] = r; Kcol[K] = c;
    K++;
  }
  fin.close();
  if (K == 1){
    fout << 0 << endl;
    fout.close();
    return 0;
  }
  
  reset(boards[0]);
  bfs_king(boards[0],Krow[0],Kcol[0]);

  for (int i = 1; i < K; ++i){
    reset(boards[i]);
    bfs_from(boards[i],Krow[i],Kcol[i]);
  }

  int output[MROW][MCOL];
  int minimum = infinity;
  for (int i = 0; i < R*C; ++i)
    output[i/C][i%C] = 0;
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j){
      for (int k = 1; k < K; ++k){
        output[i][j]+=boards[k][i][j];
        if (k == K-1 && output[i][j] < minimum)
          minimum = output[i][j];
      }
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

