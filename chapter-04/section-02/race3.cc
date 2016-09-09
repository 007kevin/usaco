/*
ID: min_j
LANG: C++
TASK: race3
Date: 09/09/2016
Anaylsis:
  There are at most 50 nodes and 100 edges therefore we can remove 
  each node and test if path is possible. As for detecting well 
  formed splitting points P, mark all nodes that come before P and 
  see if there are any paths to the marked nodes.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#define MAXP 50
using namespace std;

int P;
int course[MAXP][MAXP];
int visit[MAXP];
int visit1[MAXP];
vector<int> UP;
vector<int> SP;
// std::ostream& operator<<(std::ostream &out, const (int *C)[MAXP]){
//   out << C[0][0] << std::endl;
//   return out;
// }

bool unavoidable_point(int s, int p){
  if (s == P-1)
    return false;
  if (visit[s] == p)
    return true;
  visit[s] = p;
  for (int i = 0; i < P; ++i)
    if (course[s][i] && i != p)
      if (!unavoidable_point(i,p))
        return false;

  return true;
}

bool splitting_point(int s, int p){
  if (visit[s] == p)
    return false;
  if (visit1[s] == p)
    return true;
  visit1[s] = p;
  for (int i = 0; i < P; ++i)
    if (course[s][i] && i != p)
      if (!splitting_point(i,p))
        return false;
  return true;
}

int main(){
  ifstream fin("race3.in");
  ofstream fout("race3.out");
  assert(fin.is_open());
  assert(fout.is_open());
  int p;
  while (true){
    fin>>p;
    if (p == -1) break;
    if (p == -2) P++;
    else {
      course[P][p] = 1;
    }
  }
  
  for (int i = 1; i < P-1; ++i){
    if (unavoidable_point(0,i)){
      UP.push_back(i);
      if (splitting_point(i,i))
        SP.push_back(i);
    }
  }

  // DEBUG
  // for (int i = 0; i < P; ++i){
  //   for (int j = 0; j < P; ++j)
  //     cout << course[i][j] << " ";
  //   cout << endl;
  // }
  
  fout << UP.size();
  if (UP.size() != 0){
    fout << " ";
    for (int i = 0; i < UP.size(); ++i){
      fout << UP[i];
      if (i < UP.size()-1)
        fout << " ";
    }
  }    
  fout << endl;

  fout << SP.size();
  if (SP.size() != 0){
    fout << " ";
    for (int i = 0; i < SP.size(); ++i){
      fout << SP[i];
      if (i < SP.size()-1)
        fout << " ";
    }
  }
  fout << endl;
  
  return 0;
}
