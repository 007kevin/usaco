/*
ID: min_j
LANG: C++
TASK: sort3
Date: 02/04/2015
Analysis:
Way too slow to brute force every combination of
swaps to get to sorted.
Solution incorrect
*/
#include <iostream>
#include <fstream>
using namespace std;
int N, records[1000];
int swapcount = 1000;

int sorted(){
  for (int i = 1; i < N; ++i)
    if (records[i-1] > records[i])
      return 0;
  return 1;
}

int swap(int a, int b){
  int tmp = records[a];
  records[a] = records[b];
  records[b] = tmp;
}
  
void swapsort(int c){
  if (sorted()){
    if (c < swapcount)
      swapcount = c;
    return;
  }
  for (int i = 0; i < N - 1; ++i)
    for (int j = i + 1; j < N; ++j){
      if (records[i] > records[j]){
        swap(i, j);
        swapsort(c + 1);
        swap(i, j);
      }
    }
}

int main(){
  ifstream fin("sort3.in");
  ofstream fout("sort3.out");
  fin>>N;
  for (int i = 0; i < N; ++i)
    fin>> records[i];

  fin.close();

  swapsort(0);

  for (int i = 0; i < N; ++i)
    cout << records[i] << " ";
  cout << endl;
  
  fout << swapcount <<  endl;

  fout.close();
  return 0;
}
