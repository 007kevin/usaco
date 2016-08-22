/*
ID: min_j
LANG: C++
TASK: buylow
Date: 10/08/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <climits>
#define MAXN 5001
using namespace std;
int N;
int days[MAXN];
int dp1[MAXN]; // Let dp1[i] be longest decreasing subsequence
int dp2[MAXN]; // Let dp2[i] be number of sequences

int main(){
  ifstream fin("buylow.in");
  ofstream fout("buylow.out");
  fin>>N;
  for (int i = 1; i <= N; ++i) fin>>days[i];
  fin.close();

  int longest = 0;
  unsigned long long nsequences = 0;
  days[0] = INT_MAX;
  dp2[0] = 1;
  for (int i = 1; i <= N; ++i){
    for (int j = i-1; j >= 0; --j){
      if (days[j] > days[i])
        dp1[i] = max(dp1[i],dp1[j]+1);
    }
    set<int> S;
    for (int j = i-1; j >= 0; --j){
      if (days[j] > days[i] && dp1[i] == dp1[j]+1){
        if (S.find(days[j] - days[i]) == S.end()){
          dp2[i]+=dp2[j];
          S.insert(days[j] - days[i]);
        }
      }
    }
    longest = max(dp1[i],longest);
  }

  set<int> S;
  for (int i = 1; i <= N; ++i)
    if (dp1[i] == longest && S.find(days[i]) == S.end()){
      S.insert(days[i]);
      nsequences+=dp2[i];
    }

  fout << longest << " " << nsequences << endl;

  for (int i = 1; i <= N; ++i)
    if (dp1[i] = longest)
    cout << days[i] << "\t";
  cout << endl;

  for (int i = 1; i <= N; ++i)
    if (dp1[i] = longest)    
    cout << dp1[i] << "\t";
  cout << endl;
  
  for (int i = 1; i <= N; ++i)
    if (dp1[i] = longest)    
    cout << dp2[i] << " \t";
  cout << endl;

  fout.close();
  return 0;
}
