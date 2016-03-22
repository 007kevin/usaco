/*
ID: min_j
LANG: C++
TASK: numtri
Date: 20/03/2015
Comment: 
Recursive solution too slow. Because we only need the
max path sum, and not what the path is, it may be faster
to implement just a for loop.
Solution provided in numtri1.cc         
*/
#include <iostream>
#include <fstream>
using namespace std;
int R, maxsum;
int ntree[1000][1000];
int path[1000];
int memo[1000];

void solve(int lvl, int node, int csum){
  
  if (lvl + 1 ==  R){
    path[lvl] = ntree[lvl][node];
    int sum = 0;
    for (int i = 0; i < R; ++i){
      //      cout << path[i] << " ";
      sum+=path[i];
    }
    //    cout << sum << endl;
    maxsum = maxsum < sum ? sum : maxsum;
    return;
  }
  path[lvl] = ntree[lvl][node];
  csum = csum + path[lvl];

  if (csum  >= memo[lvl]){
    memo[lvl] = csum;
    solve(lvl + 1, node, csum);
    solve(lvl + 1, node + 1, csum);
  }
  
}


int main(){
  ifstream fin("numtri.in");
  ofstream fout("numtri.out");
  fin >> R;
  for (int i = 0 ; i < R; ++i)
    for (int j = 0; j <= i; ++j)
      fin >> ntree[i][j];
  fin.close();
  solve(0, 0, 0);
  fout << maxsum << endl;

  // for (int i = 0; i < R; ++i){
  //   cout << "level: " << i << " " << memo[i] << endl;
  // }

  
  fout.close();
  return 0;
}
