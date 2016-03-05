/*
ID: min_j
LANG: C++
TASK: milk
Date: 04/03/2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

struct farmer {
  int cost, units;
};

void swap(farmer *arr, int a, int b){
  farmer tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}
void qsort(farmer *arr, int left, int right){
  if (left >= right) return;
  swap(arr, left, (left+right)/2);
  int last = left;
  for (int i = left+1; i <= right; ++i)
    if (arr[i].cost < arr[last].cost)
      swap(arr, ++last, i);
  swap(arr, last, left);
  qsort(arr, left, last-1);
  qsort(arr, last+1, right);
}

bool cmp(farmer a, farmer b){
  return a.cost < b.cost;
}

int main(){
  FILE *fin = fopen("milk.in", "r");
  FILE *fout = fopen("milk.out", "w");
  int milk, N, min=0, bought=0;
  fscanf(fin, "%d %d", &milk, &N);
  farmer farmers[N];
  for (int i=0; i<N; ++i)
    fscanf(fin, "%d %d", &farmers[i].cost, &farmers[i].units);
  std::sort(farmers, farmers+N, cmp);
  while(bought!=milk){
    for (int i=0; i < N; i++){
      int tobuy = milk - bought;
      if (farmers[i].units > tobuy){
        min+=farmers[i].cost*tobuy;
        bought+=tobuy;
      }
      else{
        min+=farmers[i].cost*farmers[i].units;
        bought+=farmers[i].units;
      }
    }
  }
  fprintf(fout, "%d\n", min);

  fclose(fin);
  fclose(fout);

  return 0;
}
