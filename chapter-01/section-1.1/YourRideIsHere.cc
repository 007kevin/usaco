/*
ID: min_j
PROG: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (){
  ifstream fin ("ride.in");
  ofstream fout ("ride.out");
  string comet, group;
  while (fin>>comet>>group){
    int c = 1, g = 1;
    for (int i = 0; i < comet.size(); ++i)
      c *= comet[i] - 'A' + 1;
    for (int i = 0; i < group.size(); ++i)
      g *= group[i] - 'A' + 1;

    if (c % 47 == g % 47)
      fout<<"GO"<<endl;
    else
      fout<<"STAY"<<endl;
  }
  fin.close();
  fout.close();

  return 0;
}
