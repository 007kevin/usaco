/*
ID: min_j
LANG: C++
TASK: game1
Date: 09/06/2016
Anaylsis:
  Let i and j be the start and end positions
  of the board where i <= j. When i == j, we know
  the board is of one element therefore the current player
  gets that point.

  We define dp[i][j] as the optimal points the current player
  can get from the subboard positio i to j inclusive. If we wish to know
  the second player's optimal points, we subtract the current player's 
  points from the total available points for that board. 
  
  Let tot[i][j] be the total available points for that subboard.
  The recurrence relation is defined as:

  dp[i][j] = max(board[i]+(total[i+1][j]-dp[i+1][j]),
                 board[j]+(total[i][j-1]-dp[i][j-1]))
                           ^                      ^
                           +----------------------+
                           this is the optimal points
                           for the second player, since
                           that is the point current player
                           will get if playing that move
*/
#include <iostream>
#include <fstream>
#define MAXN 101
#define max(a,b) (a) < (b) ? b : a
using namespace std;
int N;
int board[MAXN];
int dp[MAXN][MAXN];  // Optimal points for board from i to j
int tot[MAXN][MAXN]; // Total points for board from i to j
int main(){
  ifstream fin("game1.in");
  ofstream fout("game1.out");
  fin>>N;
  for (int i = 0; i < N; ++i){
    fin>>board[i];
    dp[i][i] = board[i]; // Set the base cases for building dp and tot
    tot[i][i] = board[i];
  }
  fin.close();
  for (int i = 1; i < N; ++i)
    for (int j = 0; j+i < N; ++j){
      tot[j][j+i] = tot[j][j+i-1]+board[j+i];
      dp[j][j+i] = max(tot[j][j+i]-dp[j+1][j+i],
                       tot[j][j+i]-dp[j][j+i-1]);
    }
  fout << dp[0][N-1] << " " <<  tot[0][N-1] - dp[0][N-1] << endl;
  fout.close();
  return 0;
}


