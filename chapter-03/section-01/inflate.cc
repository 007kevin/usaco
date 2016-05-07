/*
ID: min_j
LANG: C++
TASK: inflate
Date: 07/05/2015
Anaylsis:
  I think we use dynamic programming to solve this
  problem
*/
#include <iostream>
#include <fstream>
using namespace std;
//#define DEBUG
#define MAX 20001

int M,N;
struct cate{
  int p,m;
};
cate pc[MAX];
int dp[MAX];
int main(){
  ifstream fin("inflate.in");
  ofstream fout("inflate.out");
  fin>>M>>N;
  int min,point,max=0;
  for (int i = 0; i < N; ++i){
    fin>>point;
    fin>>min;
    dp[min] = point;
    pc[i].p = point;
    pc[i].m = min;
  }
  for (int m = 0; m <= M; ++m){
    if (dp[m]){
      max = dp[m] > max ? dp[m] : max;
      for (int p = 0; p < N; ++p){
        if (dp[m+pc[p].m] < dp[m] + pc[p].p){
          dp[m+pc[p].m] = dp[m] + pc[p].p ;
        }
      }
    }
  }
  fout<<max<<endl;

#ifdef DEBUG
  for (int i = 0; i <= M; ++i){
    cout<<i<<": "<<dp[i]<<endl;
  }
#endif
    
  return 0;
}
