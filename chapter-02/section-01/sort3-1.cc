/*
ID: min_j
LANG: C++
TASK: sort3
Date: 02/04/2015
Analysis:
Since swaps can place at most two elements into place,
and because once the keys are sorted, there will be sections
for one, two, and three,
first optimally swap the 1, 2, and 3 into position.
Any other remaining swaps will require two swaps to rotate
the elements into place.
*/
#include <iostream>
#include <fstream>
using namespace std;
int N, swapcount, records[1000], keys[3];;

void swap(int a, int b){
  swapcount++;
  int tmp = records[a];
  records[a] = records[b];
  records[b] = tmp;
}

// index of where key starts
int skey(int b){
  int base = 0;
  for (int i = 0; i < 3; ++i)
    if (i == b)
      break;
    else
      base += keys[i];
  return base;
}

// Find index of a, in the key of b
int find(int a, int b){
  int base = skey(b);
  for (int i = base; i < base + keys[b]; ++i)
    if (records[i] == a)
      return i;
  return -1;
}

// a and b are elements to look for
// when performing optimal swaps
int optswap(int a, int b){
  for (int i = 0; i < N; ++i)
    if (records[i] == a && !(skey(a) <= i && i < skey(a) + keys[a])){
      int x = find(b, a);
      if (x != -1)
        swap(i, x);
    }
    else
      if (records[i] == b && !(skey(b) <= i && i < skey(b) + keys[b])){
        int x = find(a, b);
        if (x != -1)
          swap(i, x);
      }
}

// rotate remaining keys that were not
// optimal (hence not swapped via optswap)
void rotate_remaining(int a){
  for (int i = 0; i < N; ++i)
    if (records[i] == a && !(skey(a) <= i && i < skey(a) + keys[a])){
      int base = skey(a);
      for (int j = base; j < base + keys[a]; ++j){
        if (records[j] != a)
          swap(j, i);
      }
    }
}


int main(){
  ifstream fin("sort3.in");
  ofstream fout("sort3.out");
  fin>>N;
  for (int i = 0; i < N; ++i){
    fin>> records[i];
    keys[records[i]]++;
  }
  fin.close();

  // for (int i = 0; i < N; ++i)
  //   cout << records[i] << " ";
  // cout << endl;

  optswap(1, 2);
  optswap(1, 3);
  optswap(2, 3);
  rotate_remaining(1);
  rotate_remaining(2);
  rotate_remaining(3);


  // for (int i = 0; i < N; ++i)
  //   cout << records[i] << " ";
  // cout << endl;
  
  fout << swapcount <<  endl;

  fout.close();
  return 0;
}
