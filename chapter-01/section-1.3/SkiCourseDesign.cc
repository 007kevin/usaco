/*
ID: min_j
LANG: C++
TASK: skidesign
Date: 14/03/2015
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define MAXN 1000
int N, cost, hill[MAXN], diff[MAXN];
int carryover;

void solve(int lvl){
  while (carryover){
    int c, C;
    for (c = 0; c < N - 1; ++c)
      if (hill[c] != hill[c+1]) break;
    
    for (C = c; C >= 1 && hill[C] == hill[C-1] && carryover > 0; C--){
      carryover--;
      diff[C]++;
      hill[C]++;
      if (hill[N-1] - hill[0] <= 17){
        for (int i = 0; i < N; ++i)
          cost += diff[i] * diff[i];
        return;
      }
    }

    if (carryover > 0){
      carryover--;
      diff[C]++;
      hill[C]++;
      if (hill[N-1] - hill[0] <= 17){
        for (int i = 0; i < N; ++i)
          cost += diff[i] * diff[i];
        return;
      }
    }
  }

  if (hill[N-1] - hill[0] <= 17){
    for (int i = 0; i < N; ++i)
      cost += diff[i] * diff[i];
    return;
  }
  
  int i, raise = 0, level = lvl;
  while (level){
  for (i = 0; i < N - 1; ++i)
    if (hill[i] != hill[i+1]) break;
  
  for (int a = 0; a <= i; ++a){
    diff[a]++;
    hill[a]++;
    raise++;
  }
  level--;
  }
  
  int j;
  while (raise > 0){
    int reduce = 0;
    for (j = N-1; j >= 1; --j)
      if (hill[j] != hill[j-1]) break;
    for (int k = j; k < N; ++k){
      diff[k]++;
      hill[k]--;
      reduce++;
      if (hill[N-1] - hill[0] <= 17){
        for (int i = 0; i < N; ++i)
          cost += diff[i] * diff[i];
        return;
      }
    }
    raise-=reduce;
  }
  carryover += raise*-1;
    
  // for (int i = 0; i < N; ++i)
  //   cout << diff[i] << (diff[i] < 10 ? "  " : " ") ;
  // cout << carryover << endl << endl;

  solve(lvl);
}

int main(void){
  ifstream fin("skidesign.in");
  ofstream fout("skidesign.out");
  fin>>N;
  for (int i = 0; i < N; ++i)
    fin>>hill[i];
  fin.close();
  

  sort(hill, hill + N);

  // for (int i = 0; i < N; ++i)
  //   cout << hill[i] << (hill[i] < 10 ? "  " : " ") ;
  // cout << carryover << endl;
  solve(2);
  cout << cost << " " << "" << endl;
  fout<<cost<<endl;
  // for (int i = 0; i < N; ++i)
  //   cout << diff[i] << (diff[i] < 10 ? "  " : " ") ;
  // cout << carryover << endl;

  // for (int i = 0; i < N; ++i)
  //   cout << hill[i] << (hill[i] < 10 ? "  " : " ") ;
  // cout << carryover << endl;


  fout.close();
  return 0;
}
