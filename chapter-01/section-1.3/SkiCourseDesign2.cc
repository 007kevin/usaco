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

#define ST 10
#define END 52

#define MAXN 1000
int N, cost, hill[MAXN], diff[MAXN];

void solve(){
  for (int i = 0; i < N; ++i){
    for (int j = i+1; j < N-1; ++j){
      if(hill[
      
    }
  }

}

int main(void){
  ifstream fin("skidesign.in");
  ofstream fout("skidesign.out");
  fin>>N;
  for (int i = 0; i < N; ++i)
    fin>>hill[i];
  fin.close();
  sort(hill, hill + N);
  
  for (int i = 0; i < N; ++i){
    if (i == ST){ i = END; cout << "... ";}
    cout << hill[i] << (hill[i] < 10 ? "  " : " ") ;
  }
  cout << endl;
  
  solve();
  
  for (int i = 0; i < N; ++i){
    if (i == ST){ i = END; cout << "... ";}
    cout << hill[i] << (hill[i] < 10 ? "  " : " ") ;
  }
  cout << endl;

  fout<<cost<<endl;
  fout.close();
  return 0;
}
