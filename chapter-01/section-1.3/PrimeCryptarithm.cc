/*
ID: min_j
LANG: C++
TASK: crypt1
Date: 07/03/2015
*/
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;

int n;

void subsets(int *set, vector<int> &results , string r, int depth){
  if (depth == 0){
    results.push_back(atoi(r.c_str()));
    return;
  }
  for (int i = 0; i < n; ++i){
    char c = set[i]+'0';
    subsets(set, results, r+c, depth-1);
  }
}

int isvalid(int *set, int l, int num){
  char r[1000];
  sprintf(r, "%d", num);
  int len = strlen(r);
  if (len != l) return 0;
  for (int i = 0; i < len; ++i){
    int flag = 0;
    for (int j = 0; j < n; ++j)
      if (r[i] == set[j]+'0') flag = 1;
    if (flag == 0) return 0;
  }
  return 1;
}

int main(){
  FILE *fin = fopen("crypt1.in", "r");
  FILE *fout = fopen("crypt1.out", "w");
  fscanf(fin, "%d\n", &n);
  int N[n];
  for (int i = 0; i < n; ++i)
    fscanf(fin, "%d", &N[i]);

  vector<int> op1, op2, partials;
  subsets(N, op1, "", 3);
  subsets(N, op2, "", 2);

  int count = 0;
  vector<int>::iterator i, j;
  for (i = op1.begin(); i != op1.end(); ++i)
    for (j = op2.begin(); j != op2.end(); ++j){
      int p1, p2, res, tmp = *j;
      p1 = (tmp%10) * *i;
      tmp/=10;
      p2 = tmp * *i;
      if (isvalid(N, 3, p1) && isvalid(N, 3, p2)){
        if (isvalid(N, 4, p1 + (p2*10))){
          // cout <<" "<< *i << endl;
          // cout <<"  "<<*j<<endl;
          // cout << "-----" << endl;
          // cout <<" "<< p1 << endl;
          // cout << p2 << " " << endl;
          // cout << p1 + (p2*10) << endl;
          // cout << endl;
          count++;
        }
      }
    }

  fprintf(fout, "%d\n", count);
  fclose(fin);
  fclose(fout);
  return 0;
}
