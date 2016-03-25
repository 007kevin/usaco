/*
ID: min_j
LANG: C++
TASK: milk2
Date: 17/02/2015
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#define N 5000

typedef struct {
  unsigned long s, e;
} farmer;

bool compare(const farmer& f1, const farmer& f2){
  return f1.s < f2.s;
}

int main(){
  unsigned long s, e;
  farmer farmers[N];
  int n;
  FILE *fin = fopen("milk2.in", "r"); //1700 3200
  FILE *fout = fopen("milk2.out", "w");

  fscanf(fin, "%d", &n);
  for (int i = 0; i < n; ++i){
    fscanf(fin, "%lu %lu", &s, &e);
    farmers[i].s = s;
    farmers[i].e = e;
  }

  sort(farmers, farmers + n, &compare);

  farmer current = farmers[0];
  unsigned long max = current.e - current.s;
  unsigned long max_nm = 0;
  for (int i = 1; i < n; ++i){
    if (farmers[i].s <= current.e)
      current.e = current.e < farmers[i].e ? farmers[i].e : current.e;
    else{
      max = current.e - current.s > max ? current.e - current.s : max;
      max_nm = farmers[i].s - current.e > max_nm ? farmers[i].s - current.e : max_nm;
      current = farmers[i];
    }
  }

  fprintf(fout, "%lu %lu\n", max, max_nm);

  fclose(fin); fclose(fout);
}
