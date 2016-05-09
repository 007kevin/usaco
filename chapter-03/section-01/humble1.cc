/*
ID: min_jn
LANG: C++
TASK: humble
Date: 07/05/2015
Anaylsis:
  Create a minimum spanning tree. Starting from 1, we know what
  the adjacent nodes are by multiplying by the prime subset. 
  As we add to the min. spanning tree, we know the nth number
  in set S (since generating MST is the same as generating S 
  sequentially)

  Finding:
  O(N(N+1)/2*K) = O(N^2*K) too slow
*/
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
#define MAXK 100
#define MAXN 100000
#define inf LONG_MAX
int subS[MAXK+1];
long S[MAXN+1];
int N,K;
int counter;

int main(){
  ifstream fin("humble.in.fail");
  ofstream fout("humble.out");
  fin>>K>>N;
  for (int i = 0; i < K; ++i){
    fin>>subS[i];
  }
  S[counter++] = 1;
  while (true){
    if (counter == N+1){
      fout<<S[counter-1]<<endl;
      break;
    }
    // Find min edge
    long long min = inf;
    for (int i = 0; i < counter; ++i)
      for (int j = 0; j < K; ++j)
        if (S[i]*subS[j] > S[counter-1] && S[i]*subS[j] < min)
          min =  S[i]*subS[j];
    S[counter++] = min;
  }

  fout.close();
  return 0;
}
