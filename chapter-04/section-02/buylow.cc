/*
ID: min_j
LANG: C++
TASK: buylow
Date: 17/08/2016
Anaylsis:
  dp2[i] is the number of unique sequences of length dp1[i] if and only if 
*/
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <vector>
#include <set>
#define DEBUG
#define MAXN 5001
#define max(a,b) ((a) < (b) ? b : a)
using namespace std;

int N;
int seq[MAXN];
int dp1[MAXN]; // let dp1[i] be length of longest sequence ending in seq[i]
int dp2[MAXN]; // let dp2[i] be number of sequences of length dp1[i] ending in seq[i]
int longest;
int num_seq;

int main(){
  ifstream fin("buylow.in");
  ofstream fout("buylow.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N;
  
  for (int i = 0; i < N; ++i)
    fin>>seq[i];

  for (int i = 0; i < N; ++i){
    dp1[i] = 1;
    for (int j = i-1; j >= 0; --j){
      if (seq[j] > seq[i]){
        dp1[i] = max(dp1[i], dp1[j]+1);
      }
    }
    set<int> S;
    for (int j = i-1; j >= 0; --j){
      if (seq[j] > seq[i] &&
          dp1[j]+1 == dp1[i] &&
          S.find(seq[j]-seq[i]) == S.end()){
        S.insert(seq[j]-seq[i]);
        dp2[i]+=dp2[j];
      }
    }
    if (dp2[i] == 0) dp2[i] = 1;
    longest = max(longest, dp1[i]);
  }

  set<int> S;
  for (int i = N-1; i >= 0; --i){
    if (dp1[i] == longest &&
        S.find(seq[i]) == S.end()){
      S.insert(seq[i]);
      num_seq+=dp2[i];
    }
  }
  
#ifdef DEBUG
  for (int i = 0; i < N; ++i)
    cout << seq[i] << "\t";
  cout << endl;
  
  for (int i = 0; i < N; ++i)
    cout << dp1[i] << "\t";
  cout << endl;

  for (int i = 0; i < N; ++i)
    cout << dp2[i] << "\t";
  cout << endl;
#endif
  

  fout << longest << " " << num_seq << endl;
  
  return 0;
}
