/*
ID: min_j
LANG: C++
TASK: lgame
Date: 09/28/2016
Anaylsis:
*/
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <set>
#include <cassert>
using namespace std;

class Pointify {
  struct words {
    int point;
    list<string> L;
    words() : point(0) {};
    words(int p) : point(p) {}
  };
  unordered_map<string,words> H;
public:

 int points(string str){
    int p[] = {
      2, // a
      5, // b
      4, // c
      4, // d
      1, // e
      6, // f
      5, // g
      5, // h
      1, // i
      7, // j
      6, // k
      3, // l
      5, // m
      2, // n
      3, // o
      5, // p
      7, // q
      2, // r
      1, // s
      2, // t
      4, // u
      6, // v
      6, // w
      7, // x
      5, // y
      7, // z      
    };
    int pt = 0;
    for (char c : str)
      pt+=p[c-'a'];
    return pt;
  }
  
  Pointify(ifstream &dict){
    string str = "";
    dict >> str;
    while (str != "."){
      string word = str;
      sort(str.begin(),str.end());
      if (H.find(str) == H.end()){
        H.insert({str,words(points(str))});
        H[str].L.push_back(word);
      }
      else {
        H[str].L.push_back(word);
      }
      
      dict >> str;
    }
  }

  pair<int,vector<string>> eval(string s) {
    sort(s.begin(),s.end());
    vector<string> sol;
    vector<pair<list<string>*,list<string>*>> w;
    int maxp = 0;
    if (H.find(s) != H.end()){
      maxp = H[s].point;
      w.push_back({&H[s].L,NULL});
    }
    string str1 = "";
    string str2 = "";
    for (int i = 0; i < s.size(); ++i){
      str1+=s[i];
      for (int j = i+1; j < s.size(); ++j){
        str1+=s[j];
        for (int k = j+1; k < s.size(); ++k){
          str1+=s[k];
          str2 = "";
          for (int l = 0; l < s.size(); ++l)
            if (l != i && l != j && l != k)
              str2+=s[l];
          int p = 0;
          auto h1 = H.find(str1);
          auto h2 = H.find(str2);
          if (h1 !=  H.end()){
            p+=h1->second.point;
          }
          if (h2 != H.end()){
            p+=h2->second.point;
          }
          if (p > maxp){
            w.clear();
            maxp = p;
            pair<list<string>*,list<string>*> pair(NULL,NULL);
            if (h1 != H.end())
              pair.first = &h1->second.L;
            if (h2 != H.end())
              pair.second = &h2->second.L;
            w.push_back(pair);
          }
          if (p == maxp){
            pair<list<string>*,list<string>*> pair(NULL,NULL);
            if (h1 != H.end())
              pair.first = &h1->second.L;
            if (h2 != H.end())
              pair.second = &h2->second.L;
            w.push_back(pair);
          }

          str1.pop_back();
        }
        str1.pop_back();
      }
      str1.pop_back();
    }
    for (auto p : w){
      if (p.first != NULL && p.second != NULL){
        for (auto s1 : *p.first)
          for (auto s2 : *p.second)
            if (s1 < s2)
              sol.push_back(s1 + " " + s2);
            else
              sol.push_back(s2 + " " + s1);
      }
      else if (p.first != NULL){
        for (auto s1 : *p.first)
          sol.push_back(s1);
      }
      else if (p.second != NULL){
        for (auto s1 : *p.second)
          sol.push_back(s1);
      }
      else {}
    }
    
    sort(sol.begin(),sol.end());
    auto it = unique(sol.begin(),sol.end());
    sol.resize(distance(sol.begin(),it));
    return {maxp, sol};
  }


};

int main(){
  ifstream dict("lgame.dict");
  ifstream fin("lgame.in");
  ofstream fout("lgame.out");
  assert(dict.is_open());
  assert(fin.is_open());
  assert(fout.is_open());
  Pointify P(dict);
  string letters;
  fin >> letters;
  pair<int,vector<string>> solution = P.eval(letters);
  fout << solution.first << endl;
  for (string s : solution.second){
    fout << s << endl;
  }

  return 0;
}
