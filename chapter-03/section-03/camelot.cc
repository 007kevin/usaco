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
//#define DEBUG
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
int K,Krow[MROW*MCOL],Kcol[MROW*MCOL]; // King is when K=0

bool valid(int (*board)[MCOL], int r, int c){
  if (r < 0 || r >= R || c < 0 || c >= C)
    return false;
  return true;
}

void spa_from(int (*board)[MCOL], int r, int c){
  priority_queue<coord> Q;
  int step = 0,cr,cc;
  board[r][c] = step;
  Q.push(coord(r,c,step));
  while(!Q.empty()){
    coord cur = Q.top(); Q.pop();
    step = cur.d + 1;
    cr = cur.r-1; cc = cur.c+2;
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r-1; cc = cur.c-2;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r+1; cc = cur.c+2;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r+1; cc = cur.c-2;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r+2; cc = cur.c-1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r-2; cc = cur.c-1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r+2; cc = cur.c+1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r-2; cc = cur.c+1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
  }
}

void bfs_king(int (*board)[MCOL], int r, int c){
  priority_queue<coord> Q;
  int step = 0,cr,cc;
  board[r][c] = step;
  Q.push(coord(r,c,step));
  while(!Q.empty()){
    coord cur = Q.top(); Q.pop();
    step = cur.d + 1;
    cr = cur.r-1; cc = cur.c;
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r-1; cc = cur.c+1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r; cc = cur.c+1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }
    cr = cur.r+1; cc = cur.c+1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r+1; cc = cur.c;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r+1; cc = cur.c-1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r; cc = cur.c-1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
    cr = cur.r-1; cc = cur.c-1;    
    if (valid(board,cr,cc) && step < board[cr][cc]){
      board[cr][cc] = step;
      Q.push(coord(cr,cc,step));
    }    
  }
}

bool knight_move(const coord& cur, int r, int c){
  for (int i = 1; i < K; ++i)
    if (boards[i][r][c] - boards[i][cur.r][cur.c] == cur.d)
      return true;
  return false;
}

bool backtrack(int (*board)[MCOL],int r, int c, coord cur){
  if (!knight_move(cur,r,c))
    return false;
    
  int cr,cc,step = cur.d + 1;
  cr = cur.r-1; cc = cur.c+2;
  if (valid(board,cr,cc))
    if (backtrack(board,r,c,coord(cr,cc,step)))
      board[cr][cc] = step;
        
  cr = cur.r-1; cc = cur.c-2;    
  if (valid(board,cr,cc))
    if (backtrack(board,r,c,coord(cr,cc,step)))
      board[cr][cc] = step;

  cr = cur.r+1; cc = cur.c+2;    
  if (valid(board,cr,cc))
    if (backtrack(board,r,c,coord(cr,cc,step)))
      board[cr][cc] = step;
  
  cr = cur.r+1; cc = cur.c-2;    
  if (valid(board,cr,cc))
    if (backtrack(board,r,c,coord(cr,cc,step)))
      board[cr][cc] = step;
  
  cr = cur.r+2; cc = cur.c-1;    
  if (valid(board,cr,cc))
    if (backtrack(board,r,c,coord(cr,cc,step)))
      board[cr][cc] = step;
  
  cr = cur.r-2; cc = cur.c-1;    
  if (valid(board,cr,cc))
    if (backtrack(board,r,c,coord(cr,cc,step)))
      board[cr][cc] = step;
  
  cr = cur.r+2; cc = cur.c+1;    
  if (valid(board,cr,cc))
    if (backtrack(board,r,c,coord(cr,cc,step)))
      board[cr][cc] = step;
  
  cr = cur.r-2; cc = cur.c+1;    
  if (valid(board,cr,cc))
    if (backtrack(board,r,c,coord(cr,cc,step)))
      board[cr][cc] = step;
  
  return true;
}

int nearest_knight(int (*board)[MCOL]){
  priority_queue<coord> Q;
  Q.push(coord(Krow[0],Kcol[0],0));
  while (!Q.empty()){
    coord cur = Q.top(); Q.pop();
    if (board[cur.r][cur.c] != infinity)
      return cur.d;
    
    int cr,cc,step = cur.d + 1;
    cr = cur.r-1; cc = cur.c;
    if (valid(board,cr,cc))
      Q.push(coord(cr,cc,step));

    cr = cur.r-1; cc = cur.c+1;    
    if (valid(board,cr,cc))
      Q.push(coord(cr,cc,step));

    cr = cur.r; cc = cur.c+1;    
    if (valid(board,cr,cc))
      Q.push(coord(cr,cc,step));

    cr = cur.r+1; cc = cur.c+1;    
    if (valid(board,cr,cc))
      Q.push(coord(cr,cc,step));

    cr = cur.r+1; cc = cur.c;    
    if (valid(board,cr,cc))
      Q.push(coord(cr,cc,step));

    cr = cur.r+1; cc = cur.c-1;    
    if (valid(board,cr,cc))
      Q.push(coord(cr,cc,step));

    cr = cur.r; cc = cur.c-1;    
    if (valid(board,cr,cc))
      Q.push(coord(cr,cc,step));

    cr = cur.r-1; cc = cur.c-1;    
    if (valid(board,cr,cc))
      Q.push(coord(cr,cc,step));
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
  ifstream fin("camelot.in");
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
    spa_from(boards[i],Krow[i],Kcol[i]);
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
  int solution = infinity;
  int crossref[MROW][MCOL];
  for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j){
      if (output[i][j] == minimum){
        reset(crossref);
        crossref[i][j] = 0;
        backtrack(crossref,i,j,coord(i,j,0));
        int near =  nearest_knight(crossref);
        if (near < solution)
          solution = near;
      }
    }
  fout << minimum + solution << endl;
  
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

  debugprint(crossref);
  //  cout << near << endl;
#endif
  
  fout.close();  
  return 0;
}

