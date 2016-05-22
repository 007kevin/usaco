/*
ID: min_j
LANG: C++
TASK: msquare
Date: 18/05/2015
Anaylsis:
  Dijkstra's algorithm.
  Vertices are permutations, edges are combination of moves.

  Solution is correct... but running time is too slow for passing the
  online judge.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
//#define DEBUG
using namespace std;
map<string,string> vertices;
string SOL;

string moveA(string cur){
  string res = "";
  for (int i = 7; i >=0; --i)
    res+=cur[i];
  return res;
}

string moveB(string cur){
  string res = "";
  res+= cur[3];
  res+=cur.substr(0,3);
  res+=cur.substr(5,3);
  res+=cur[4];
  return res;
}

string moveC(string cur){
  string res = cur;
  res[1] = cur[6];
  res[2] = cur[1];
  res[5] = cur[2];
  res[6] = cur[5];
  return res;
}

int pathcmp(const string &p1, const string &p2){
  if (p1.length() == p2.length())
    return p1.compare(p2);
  if (p1.length() > p2.length())
    return 1;
  return -1;
}

int main(){
  ifstream fin("msquare.in");
  ofstream fout("msquare.out");
  string init = "12345678";
  string target = "";
  for (int i = 0; i < 8; ++i){
    string input;
    fin>>input;
    target+=input;
  }
  fin.close();
  vertices.insert(pair<string,string>(init,""));
  map<string,string>::iterator it;
  pair<map<string,string>::iterator,bool> ret;
  pair<string,string> minv;
#ifdef DEBUG
  int count = 0;
#endif
  if (init.compare(target) == 0) // Edge case of trivial problem
    SOL = "";
  else
    while(true){
      // find unvisited vertex with min distance to source
      minv = pair<string,string>("","");
      string adj,apath;
      for (it = vertices.begin(); it != vertices.end(); ++it){
      
        adj = moveA(it->first);
        apath = it->second+"A";
        // if true, found unvisted permutation
        if (vertices.find(adj) == vertices.end())
          if (minv.first == "" || pathcmp(minv.second,apath) > 0)
            minv = pair<string,string>(adj,apath);
      
        adj = moveB(it->first);
        apath = it->second+"B";
        // if true, found unvisted permutation      
        if (vertices.find(adj) == vertices.end())
          if (minv.first == "" || pathcmp(minv.second,apath) > 0)
            minv = pair<string,string>(adj,apath);
      
        adj = moveC(it->first);
        apath = it->second+"C";
        // if true, found unvisted permutation      
        if (vertices.find(adj) == vertices.end())
          if (minv.first == "" ||pathcmp(minv.second,apath) > 0)
            minv = pair<string,string>(adj,apath);
      }
    
      if (minv.first.compare(target) == 0){
        SOL = minv.second;
        break;
      }
      ret = vertices.insert(minv);
      if (ret.second == false){
        if (pathcmp(ret.first->second,minv.second) > 0)
          ret.first->second = minv.second;
      }
    
    
#ifdef DEBUG    
    if (count++ == 10)
      break;
#endif    
    cout << minv.first << " " << minv.second << " " << vertices.size() << endl;

    
  }

#ifdef DEBUG  
  cout << "Hash -> " << endl;
  for (it = vertices.begin(); it != vertices.end(); ++it){
    cout << it->first << ":" << it->second << endl;
  }
#endif
  int len = SOL.length();
  int printed = 0;
  string sub;
  fout << len << endl;
  while (printed <= len){
    fout << SOL.substr(printed,60) << endl;
    printed+=60;
  }
  fout.close();
  return 0;
}

