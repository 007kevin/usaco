/*
ID: min_j
LANG: C++
TASK: job
Date: 20/07/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#define MAXN 1001
#define MAXM 31
#define max(a,b) ((a) < (b) ? b : a)
using namespace std;

int N,A,B;
int M1[MAXM];
int M2[MAXM];
int jobs1[MAXN];
int jobs2[MAXN];

void greedy(int *jobs, int *M, int m){
  int t = 1;
  int n = 0;
  int last_c = 0;
  while (n < N){
    int c = 0;
    for (int i = 0; i < m; ++i)
      c+=t/M[i];
    c-=last_c;
    last_c = c+last_c;
    while (n < N && c > 0){
      jobs[n++] = t;
      c--;
    }
    t++;
  }
}

int main(){
  ifstream fin("job.in");
  ofstream fout("job.out");
  fin>>N>>A>>B;
  for (int i = 0; i < A; ++i)
    fin>>M1[i];
  for (int i = 0; i < B; ++i)
    fin>>M2[i];
  fin.close();

  greedy(jobs1,M1,A);
  greedy(jobs2,M2,B);

  // cout << "A: ";
  // for (int i = 0; i < N; ++i)
  //   cout << jobs1[i] << " ";
  // cout << endl;
  
  // cout << "B: ";  
  // for (int i = 0; i < N; ++i)
  //   cout << jobs2[i] << " ";
  // cout << endl;

  int maxtime = 0;
  for (int i = 0; i < N; ++i)
    maxtime = max(maxtime, jobs1[i]+jobs2[N-i-1]);
  
  fout << jobs1[N-1] << " " << maxtime << endl;
  
  fout.close();
  return 0;
}
