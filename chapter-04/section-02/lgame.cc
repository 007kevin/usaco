/*
ID: min_j
LANG: C++
TASK: lgame
Date: 10/07/2016
Anaylsis:
*/
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

int eval_pts(const string &str){
  int p[] = {2,5,4,4,1,6,5,5,1,7,6,3,5,
          // a b c d e f g h i j k l m 
             2,3,5,7,2,1,2,4,6,6,7,5,7};
          // n o p q r s t u v w x y z
  int pt = 0;
  for (int i = 0; i < str.size(); ++i)
    pt+=p[str[i]-'a'];
  return pt;        
}                 

void nck(set<pair<string,string> > &p, string &s, vector<bool> &v, int l, int k){
  if (count(v.begin(),v.end(),true) == k){
    string s1 = "";
    string s2 = "";
    for (int i = 0; i < v.size(); ++i)
      if (v[i]) s1+=s[i];
      else s2+=s[i];
    if (s1 < s2)
      p.insert(pair<string,string>(s1,s2));
    else
      p.insert(pair<string,string>(s2,s1));

    if (s2.size() > 3){
      string s3 = "";
      for (int i = 0; i < s2.size(); ++i){
        for (int j = 0; j < s2.size(); ++j)
          if (i != j) s3+=s2[j];
        if (s1 < s3)
          p.insert(pair<string,string>(s1,s3));
        else
          p.insert(pair<string,string>(s3,s1));
        s3 = "";
      }
    }
  }
  for (int i = l+1; i < s.size(); ++i){
    v[i] = true;
    nck(p,s,v,i,k);
    v[i] = false;
  }
}

int main(){
  ifstream fin("lgame.in");
  ofstream fout("lgame.out");
  ifstream dict("lgame.dict");
  assert(fin.is_open());
  assert(fout.is_open());
  assert(dict.is_open());
  string sw;
  string w;
  string str;
  set<string> solution;
  int maxp = 0;
  map<string,vector<string> > M;
  while(dict>>sw){
    if (sw == ".") break;
    w = sw;
    sort(sw.begin(),sw.end());
    M[sw].push_back(w);
  }
  fin>>str;
  sort(str.begin(),str.end());
  set<pair<string,string> > p;
  vector<bool> v(str.size(),false);
  for (int i = str.size()/2; i<= str.size(); ++i)
    nck(p,str,v,-1,i);

  for (set<pair<string,string> >::iterator i = p.begin(); i != p.end(); ++i){
    int pts1 = 0;
    int pts2 = 0;
    if (M.find(i->first) != M.end())
      pts1+=eval_pts(i->first);
    if (M.find(i->second) != M.end()){
      pts2+=eval_pts(i->second);
    }

    if (pts1+pts2 == 0 || pts1+pts2 < maxp)
      continue;
    
    if (pts1+pts2 > maxp){
      maxp = pts1+pts2;
      solution.clear();
    }
    
    if (pts1 && pts2){
      vector<string> s1 = M[i->first];
      vector<string> s2 = M[i->second];
      for (int j = 0; j < s1.size(); ++j)
        for (int k = 0; k < s2.size(); ++k)
          if (s1[j] < s2[k])
            solution.insert(s1[j]+" "+s2[k]);
          else solution.insert(s2[k]+" "+s1[j]);
    }
    else if (pts1){
      vector<string> s1 = M[i->first];
      solution.insert(s1.begin(),s1.end());
    }
    else {
      vector<string> s2 = M[i->second];
      solution.insert(s2.begin(),s2.end());
    }
  }

  fout << maxp << endl;
  for (set<string>::iterator i = solution.begin(); i != solution.end(); ++i)
    fout << *i << endl;

  fin.close();
  fout.close();
  dict.close();
  return 0;
}
