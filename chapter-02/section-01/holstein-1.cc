/*
ID: min_j
LANG: C++
TASK: holstein
Date: 04/04/2015
Analysis:
Breath first search
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

bool feed_available(vector<int>& a, int b){
  if (find(a.begin(), a.end(), b) == a.end())
    return true;
  return false;
}

bool exist(list<vector<int> >& nodes, vector<int>& node){
  list<vector<int> >::const_iterator i;
  for (i = nodes.begin(); i != nodes.end(); ++i){
    if (i->size() != node.size())
      continue;
    bool same = true;
    for (int j = 0; j < i->size(); ++j){
      if ((*i)[j] != node[j]){
        same = false;
        break;
      }
    }
    if (same)
      return true;
  }
  return false;
}

void solve(){
  list<vector<int> > nodes;
  for (int i = 0; i < G; ++i){
    vector<int> node;
    node.push_back(i);
    nodes.push_back(node);
  }
  int processed_lvl = 1;
  while (!nodes.empty()){

    /* DEBUG */
    list<vector<int> >::const_iterator test;
    cout << "************* s:" << solution.size() << endl;
    for (test = nodes.begin(); test != nodes.end(); ++test){
      cout << test->size() << " ";
      for (int i = 0; i < test->size(); ++i)
        cout << (*test)[i] + 1 << " ";
      cout << endl;
    }
    /* DEBUG */

    vector<int> node = nodes.front();
    nodes.pop_front();

    if (node.size() > processed_lvl)
      processed_lvl = node.size();

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
      if (solution.size() == 0 || (node.size() == processed_lvl && node.size() < solution.size()))
        for (int i = 0; i < G; ++i){
          if (feed_available(node, i)){
            vector<int> newnode = node;
            newnode.push_back(i);
            sort(newnode.begin(), newnode.end());
            if (!exist(nodes, newnode))
              nodes.push_back(newnode);
          }
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

  solve();

  fout << solution.size() << " ";
  int i;
  for (i = 0; i < solution.size() - 1; ++i)
    fout << solution[i] + 1 << " ";
  fout << solution[i] + 1 << endl;
  

  fout.close();
  return 0;
}
