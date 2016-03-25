/*
ID: min_j
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
struct account {
  int cash, gain;
};

int main(){
  ifstream fin ("gift1.in");
  ofstream fout ("gift1.out");
  // istream& fin = cin;
  // ostream& fout = cout;
  int np;
  fin>>np;
  vector<pair<string, account> > NP;
  vector<pair<string, account> >::iterator ni, vi;
  string name;
  for (int i = 0; i < np; i++){
    fin>>name;
    pair<string, account> rec(name, {0,0});
    NP.push_back(rec);
  }

  for (int i = 0; i < np; ++i){
    int cash, gm, spend;
    string gname;
    fin>>name>>cash>>gm;
    for (ni = NP.begin(); ni != NP.end(); ++ni)
      if (ni->first == name) break;
    ni->second.cash+=cash;
    if (gm == 0) spend = 0;
    else
      spend = cash/gm;
    for (int j = 0; j < gm; ++j){
      fin>>gname;
      for (vi = NP.begin(); vi != NP.end(); ++vi)
        if (vi->first == gname) break;
      vi->second.gain+=spend;
      ni->second.gain-=spend;
    }
  }

  for (vi = NP.begin(); vi != NP.end(); ++vi)
    fout<<vi->first<<" "<<vi->second.gain<<endl;

  return 0;
}

