/*
ID: min_j
LANG: C++
TASK: holstein
Date: 04/04/2015
Analysis:
Depth First Search
Solution correct.
Found that we didn't need to keep track the feed test feed combinations.
We also didn't need to check whether a scoop was included, for checking
if the scoop to be added was greater than the last scoop (line 70)
would solve two problems:
 1) Solution will be sorted
 2) No feed will be included twice.
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

#define MAXV 25
#define MAXVI 1000 //Max vitamin integers
#define MAXG 15

int V, G;
int vitamins[MAXV];
int feeds[MAXG][MAXVI];
vector<int> solution;

bool requirements_met(vector<int>& a){
  int vita[V];
  // zero out test array
  for (int i = 0; i < V; ++i)
    vita[i] = 0;
  for (int i = 0; i < a.size(); ++i)
    for (int j = 0; j <= V; ++j)
      vita[j]+=feeds[a[i]][j];
  for (int i = 0; i < V; ++i)
    if (vita[i] < vitamins[i])
      return 0;
  return 1;
}

void solve(vector<int> node){

  cout << node.size() << " ";
  for (int i = 0 ; i < node.size(); ++i)
    cout << node[i] << " ";
  cout << endl;
  
  if (requirements_met(node)){
    if (node.size() < solution.size() || solution.size() == 0){
      solution = node;
    }
    if (node.size() == solution.size()){
      int n = 0;
      int s = 0;
      for (int i = 0; i < solution.size(); ++i){
        n+=node[i];
        s+=solution[i];
      }
      if (n < s)
        solution = node;
    }
  }
  else {
    for (int i = 0; i < G; ++i){
      if (node.size() == 0 || i > node[node.size()-1]){
        vector<int> newnode = node;
        newnode.push_back(i);
        solve(newnode);
      }
    }
  }
}

int main(){
  ifstream fin("holstein.in");
  ofstream fout("holstein.out");
  fin>>V;
  for (int i = 0; i < V; ++i)
    fin>>vitamins[i];
  fin>>G;
  for (int i = 0; i < G; ++i)
    for (int j = 0; j < V; ++j)
      fin>>feeds[i][j];
  fin.close();

  vector<int> empty;
  solve(empty);

  fout << solution.size() << " ";
  int i;
  for (i = 0; i < solution.size() - 1; ++i)
    fout << solution[i] + 1 << " ";
  fout << solution[i] + 1 << endl;
  
  fout.close();
  return 0;
}
