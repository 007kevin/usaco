#include <iostream>
#include <fstream>
using namespace std;
int main(){
  ofstream fout("camelot.max");
  for (int i = 0; i < 26; ++i)
    for (int j = 0; j < 30; ++j)
      fout << (char) ('A'+i) << " " << j+1 << endl;
  fout.close();
  return 0;
}
  
