/*
ID: min_j
LANG: C++
TASK: subset
Date: 10/04/2015
Analysis:
If sum of 1..N is odd, then there are no partitions of equal sum
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXN 39
#define UL unsigned long
int N;
int ans[MAXN+1];
int sums[MAXN+1];
/*
  last - keep track of last element included in the set
  csum - current sum of the set
*/
void solve(int n, int last, int csum, int sum, int &nsets){
  if (csum == sum-csum){
    nsets++;
    return;
  }
  for (int i = 1; i <= n; ++i){
    if (i > last && csum + i <= sum/2){
      solve(n, i, csum + i, sum, nsets);
    }
  }
}

int main(){
  ifstream fin("subset.in");
  ofstream fout("subset.out");
  fin >> N;
  fin.close();

  int sum = 0;
  for (int i = 1; i <= N; ++i){
    sum+=i;
    int nsets = 0;
    sums[i] = sum;
    solve(i-1,0,0,sum,nsets);
    ans[i] = nsets;
  }

  //DEBUG
  for (int i = 1; i <= N; ++i){
    cout << i << ": " << ans[i] << " sum: " << sums[i] << endl;
  }

  fout.close();
  return 0;
}
