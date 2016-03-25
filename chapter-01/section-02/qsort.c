#include <stdio.h>
void swap(int *arr, int a, int b){
  int tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}
void qsort(int *arr, int left, int right){
  if (left >= right) return;
  int mid = (left + right) / 2;
  swap(arr, left, mid);
  int last = left;
  for (int i = left + 1; i <= right; ++i)
    if (arr[i] < arr[left])
      swap(arr, i, ++last);
  swap(arr, left, last);
  qsort(arr, left, last - 1);
  qsort(arr, last + 1, right);
}
int main(){
  int arr[11] = {0,3,2,1,8,6,5,7,4,9,6};
  qsort(arr, 0, 10);
  for (int i = 0; i < 11; ++i)
    printf("%d ", arr[i]);
  putchar('\n');
}
