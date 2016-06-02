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
  int r,c;
  coord(int row,int col){
    r = row; c = col;
  };
};
char piece[MROW][MCOL];
int board[MROW][MCOL];

bool valid(int r, int c){
  if (r < 0 || r >= R || c < 0 || c >= C ||
      board[r][c] != infinity)
    return false;
  return true;
}

void bfs_from(int r, int c){
  queue<coord> Q;
  int step = 0;
  board[r][c] = step++;
  Q.push(coord(r,c));
  while(!Q.empty()){
    coord cur = Q.front(); Q.pop();
    if (valid(cur.r-1,cur.c+3)){
      board[cur.r-1][cur.c+3] = step;
      Q.push(coord(cur.r-1,cur.c+3));
    }
  }

}

int main(){
  ifstream fin("camelot.in");
  ofstream fout("camelot.out");
  assert(fin.is_open() && fout.is_open());
  fin>>R>>C;
  for (int i = 0; i < R*C; ++i)
    board[i/C][i%R] = infinity;
  char col,row;
  fin>>col>>row;
  row -= '0'+1; col-='A';
  piece[row][col] = 'K';
  while (fin>>col>>row){
    row-='0'+1; col-='A';
    piece[row][col] = 'k';
  }
  fin.close();

  bfs_from(0,0);

#ifdef DEBUG
  cout << "  ";
  for (int i = 0; i < C; ++i)
    cout << (char) ('A'+i);
  cout << endl;
  for (int i = 0; i < R; ++i){
    cout << i << ' ';
    for (int j = 0 ; j < C; ++j){
      if (piece[i][j] == 0)
        cout << '-';
      else
        cout << piece[i][j];
    }
    cout << endl;
  }
#endif
  
  fout.close();  
  return 0;
}

