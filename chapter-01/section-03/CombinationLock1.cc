/*
ID: min_j
LANG: C++
TASK: combo
Date: 09/03/2015
Comment:
Last ditch effort required using c++ sets
*/
#include <stdio.h>
#include <set>
#include <string>
#include <sstream>

using namespace std;

int getadj(int dial, int n){
  int r = n%dial;
  if (r == 0)
    return dial;
  if (r < 0)
    return r+dial;
  return r;
}

int main(){
  FILE *fin = fopen("combo.in", "r");
  FILE *fout = fopen("combo.out", "w");
  int dial, fc[3], mc[3], overlap[3];
  fscanf(fin, "%d", &dial);
  fscanf(fin, "%d%d%d", &fc[0], &fc[1], &fc[2]);
  fscanf(fin, "%d%d%d", &mc[0], &mc[1], &mc[2]);
  set<string> ans;
  
  for (int i = -2; i <= 2; ++i)
    for (int j = -2; j <= 2; ++j)
      for (int k = -2; k <= 2; ++k){
        ostringstream out;
        out<<getadj(dial,i+fc[0])<<","<<getadj(dial,j+fc[1])<<","<<getadj(dial,k+fc[2]);
        ans.insert(out.str());
        out.str("");
        out<<getadj(dial,i+mc[0])<<","<<getadj(dial,j+mc[1])<<","<<getadj(dial,k+mc[2]);
        ans.insert(out.str());
        out.str("");
      }
  fprintf(fout, "%lu\n", ans.size());
    


  fclose(fin);
  fclose(fout);
  return 0;
}
