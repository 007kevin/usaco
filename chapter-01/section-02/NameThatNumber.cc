/*
ID: min_j
LANG: C++
TASK: namenum
Date: 22/02/2015
COMMENT:
  Although this solution is correct, a clever approach would have
  been to map the dictionary to the input, then print all matches
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
#define N 3
using namespace std;

set<string> names;
vector<string> comb;
vector<string> valid;

string convert(const char n){
  switch(n){
  case '2':
    return "ABC";
  case '3':
    return "DEF";
  case '4':
    return "GHI";
  case '5':
    return "JKL";
  case '6':
    return "MNO";
  case '7':
    return "PRS";
  case '8':
    return "TUV";
  case '9':
    return "WXY";
  }
}

void possiblenames(string val){
  if (val.size() == comb.size()){
    set<string>::iterator i;
    i = names.find(val);
    if (i != names.end())
      valid.push_back(val);
  }
  else {
    for (int i = 0; i < N; ++i)
      possiblenames(val + comb[val.size()][i]);
  }
}

int main(){
  ifstream dict ("dict.txt");
  ifstream fin ("namenum.in");
  ofstream fout ("namenum.out");

  string word;
  while (dict>>word)
    names.insert(word);
  string brandnum;
  fin>>brandnum;
  for (int i = 0; i < brandnum.size(); ++i)
    comb.push_back(convert(brandnum[i]));
  possiblenames("");
  sort(valid.begin(), valid.end());
  vector<string>::iterator i;
  if (valid.size() != 0){
  for (i = valid.begin(); i != valid.end(); ++i)
    fout << *i << endl;
  }
  else
    fout << "NONE" << endl;

    
  fin.close();
  fout.close();
  return 0;
}
