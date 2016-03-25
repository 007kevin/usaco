/*
ID: min_j
LANG: C++
TASK: wormhole
Date: 10/03/2015
Comments:
Recursively create all combinations of pairs with global variables,
Check if cycles exist with mapping of next_right array
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXN 12
int N, X[MAXN+1], Y[MAXN+1];
int partner[MAXN+1];
int next_right[MAXN+1];

bool cycle(){
  for (int i = 1; i <=N; ++i){
    int pos = i;
    for (int j = 1; j <= N; ++j)
      pos = next_right[partner[pos]];
    if (pos != 0)
      return true;
  }
  return false;
}

int solution(void){
  int i, total = 0;
  for (i = 1; i <= N; ++i)
    if (partner[i] == 0) break;

  // Basecase
  if (i > N){
    if (cycle()) return 1;
    return 0;
  }
  
  for (int j = i+1; j <= N; ++j)
    if (partner[j] == 0){
      partner[i] = j;
      partner[j] = i;
      total+=solution();
      partner[i] = partner[j] = 0;
    }
  return total;
  
}

int main(void){
  ifstream fin("wormhole.in");
  ofstream fout("wormhole.out");
  fin>>N;
  for (int i = 1; i <= N; ++i) fin >> X[i] >> Y[i];
  fin.close();
  // Set up next_right array
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= N; ++j){
      if (X[j] > X[i] && Y[i] == Y[j])
        if (next_right[i] == 0 || X[j] - X[i] < X[next_right[i]] - X[i])
          next_right[i] = j;
    }
  fout << solution() << endl;
  fout.close();
  return 0;
}
