/*
ID: min_j
LANG: C++
TASK: beads
Date: 15/02/2015
Start: 7:45 pm 
End: 11:34 pm 16/02/2015
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#define MAXN 350
using namespace std;

int beadcount(list<char>& beads){
  int c1 = 1, c2 = 1, n = beads.size();
  list<char>::const_iterator si, ei;
  si = beads.begin(); ei = beads.end();
  char color = *si++;
  while (si != ei && c1 + c2 != n){
    if (color == 'w') color = *si;
    if (color != 'w' && *si != 'w' && color != *si)
      break;
    c1++;
    si++;
  }
  list<char>::const_reverse_iterator ri, re;
  ri = beads.rbegin(); re = beads.rend();
  color = *ri++;
  while (ri != re && c1 + c2 != n){
    if (color == 'w') color = *ri;
    if (color != 'w' && *ri != 'w' && color != *ri)
      break;
    c2++;
    ri++;
  }
  return c1 + c2;
}

int main(){
  FILE *fin = fopen("beads.in", "r");
  FILE *fout = fopen("beads.out", "w");
  int n, counter = 1, max = 2;
  char str[MAXN];
  list<char> beads;
  fscanf(fin, "%d\n%s", &n, str);
  int i = 0;
  while (str[i]) beads.push_back(str[i++]);
  for (i = 0; i < n; ++i){
    int count = beadcount(beads);
    max = count > max ? count : max;
    beads.push_back(beads.front());
    beads.pop_front();
  }
  
  fprintf(fout, "%d\n", max);
  fclose(fin); fclose(fout);
  return 0;
}
