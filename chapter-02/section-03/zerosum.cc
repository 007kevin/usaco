/*
ID: min_j
LANG: C++
TASK: zerosum
Date: 20/04/2015
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;
int N;
vector<string> sol;

int zerosum(string s){
  int sum = 0;
  char op = '+';
  for (int i = 0; i < s.size(); ++i){
    if (isdigit(s[i])){
      int n = s[i] - '0';
      if (i+1 < s.size() && s[i+1] == ' '){
        n*=10;
        n+=s[i+2]-'0';
        i+=2;
      }
      switch(op){
      case '+':
        sum+=n; break;
      case '-':
        sum-=n; break;
      }
    }
    else
      op = s[i];
  }
  return sum;
}

void solve(string s, int n){
  ostringstream o;
  o << s << n;
  if (n == N){
    if (zerosum(o.str()) == 0)
      sol.push_back(o.str());
    return;
  }
  solve(o.str()+'+',n+1);
  solve(o.str()+'-',n+1);
  if (o.str().size() == 1 || o.str().size() > 0 && o.str()[o.str().size()-2] != ' ')
    solve(o.str()+' ',n+1);  
}

int main(){
  ifstream fin("zerosum.in");
  ofstream fout("zerosum.out");
  fin >> N;
  fin.close();

  solve("", 1);
  sort(sol.begin(), sol.end());
  for (int i = 0; i < sol.size(); ++i)
    fout << sol[i] << endl;

  fout.close();
  return 0;
}
