#include <iostream>
#include <fstream>
#include <climits>
#include <algorithm>
#include <vector>
#define MAXN 32
#define MAXM 1000
using namespace std;
int R[MAXN+1][MAXN+1];
int T[MAXN+1][MAXN+1];
int V[MAXN+1];
int N,M;
int minR, truck;
int minT;
vector<int> trucks;

int flow(int n, int c){
  if (n == N) return c;
  for (int i = 1; i <= N; ++i){
    if (R[n][i] && V[n] == 0){
      int w;
      V[n]++;
      if (w = flow(i,min(c,R[n][i]))){
        R[n][i]-=w;
        R[i][n]+=w;
        V[n]--;      
        return w;
      }
      V[n]--;      
    }
  }
  return 0;
}

void print(){
  cout << '\t';
  for (int i = 0; i <= N; ++i)
    cout << i << '\t';
  cout << endl;
  for (int i = 0; i <= N; ++i){
    cout << i << '\t';
    for (int j = 0; j <= N; ++j)
      cout << R[i][j] << '\t';
    cout << endl;
  }
  cout << endl;
}

int main(){
  ifstream fin("milk6.in");
  ofstream fout("milk6.out");
  fin >> N >> M;
  int n,m;
  for (int i = 0; i < M; ++i){
    fin>>n>>m;
    T[n][m] = i+1;
    fin >> R[n][m];
  }

  print();
  int w;
  while (w = flow(1,INT_MAX)){
    print();
    cout << w << endl;
  }

  sort(trucks.begin(), trucks.end());
  fout << minT << " " << trucks.size() << endl;
  for (int i = 0; i < trucks.size(); ++i)
    fout << trucks[i] << endl;
  
  fin.close();
  fout.close();
  return 0;
}
