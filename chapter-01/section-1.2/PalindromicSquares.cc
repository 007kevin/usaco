/*
ID: min_j
LANG: C++
TASK: palsquare
Date: 23/02/2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int pow(int b, int e){
  int i = 1;
  while (e--)
    i*=b;
  return i;
}

int ispal(char *num){
  int i = 0;
  int j = strlen(num) - 1;
  while(i < j){
    if (num[i] != num[j]) return 0;
    i++; j--;
  }
  return 1;
}

void returnbase(char *output, int n, int b){
  int ans[100];
  int idx = 0;
  while (n){
    ans[idx++] = (n%b);
    n/=b;
  }
  output[0] = '\0';
  while (--idx >= 0)
    sprintf(output, "%s%c", output, ans[idx] < 10 ? ans[idx]+'0' : 'A' + (ans[idx]-10));
}

int main(){
  FILE *fin = fopen("palsquare.in", "r");
  FILE *fout = fopen("palsquare.out", "w");
  int base;
  fscanf(fin, "%d", &base);
  for (int i = 1; i <=300; ++i){
    char a[100];
    char b[100];
    returnbase(a, i, base);
    returnbase(b, i*i, base);
    if (ispal(b))
      fprintf(fout, "%s %s\n", a, b);
  }
}
