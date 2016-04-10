/*
ID: min_j
LANG: C++
TASK: subset
Date: 10/04/2015
Analysis:
- If sum of 1..N is odd, then there are no partitions of equal sum
- By looking for partitions where N is not included, we avoid
  double counting partitions (i.e the for loop in solve() goes 1..N-1)
*/
#include <iostream>
#include <fstream>
using namespace std;
#define MAXN 39
int N;
int SUM;
int nsets;

/*
  last - keep track of last element included in the set
  csum - current sum of the set
*/
void solve(int last, int csum){
  if (csum == SUM-csum){
    nsets++;
    return;
  }
  for (int i = 1; i < N; ++i){
    if (i > last && csum + i <= SUM/2){
      solve(i, csum + i);
    }
  }
}

int main(){
  ifstream fin("subset.in");
  ofstream fout("subset.out");
  fin >> N;
  fin.close();
  for (int i = 1; i <= N; ++i)
    SUM+=i;
  solve(0,0);

  cout << nsets << endl;

  fout.close();
  return 0;
}
