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

void solve(){
  int i, j;
  for (i = 0; i < N - 1; ++i)
    if (hill[i] != hill[i+1]) break;
  for (j = N-1; j > 1; --j)
    if (hill[j] != hill[j-1]) break;

  if (hill[j] - hill[i] <= 17){
    int cost = 0;
    for (int i = 0; i < N; ++i)
      cost+= diff[i] * diff[i];
    return;
  }

  for (int a = 0; a <= i; ++a){
    diff[a]++;
    hill[a]++;
  }
  for (int b = j; b >= 0; --b){
    diff[b]++;
    hill[b]--;
  }

  solve();

  
  cout << i << " " << j << endl;
}

int main(void){
  ifstream fin("skidesign.in");
  ofstream fout("skidesign.out");
  //ostream &fout = cout;

  fin>>N;
  for (int i = 0; i < N; ++i)
    fin>>hill[i];
  fin.close();
  sort(hill, hill + N);
  solve();
  fout<<cost<<endl;
  //  fout.close();
  return 0;
}
