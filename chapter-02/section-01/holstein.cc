/*
ID: min_j
LANG: C++
TASK: holstein
Date: 04/04/2015
Analysis:

*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define MAXV 25
#define MAXVI 1000 //Max vitamin integers
#define MAXG 15

int V, G;
int vitamins[MAXV];
int feeds[MAXG][MAXVI];
int scoops, current[MAXG];
int minscoops, solution[MAXG];

int feed_available(int a){
  for (int i = 0; i < scoops; ++i)
    if (current[i] == a)
      return 0;
  return 1;
}

// Check if current meets the vitamin requirements
int requirements_met(){
  int vita[V];
  // zero out test array
  for (int i = 0; i < V; ++i)
    vita[i] = 0;
  // sum current into test array
  for (int i = 0; i < scoops; ++i)
    for (int j = 0; j < V; ++j)
      vita[j] += feeds[current[i]][j];
  // compare against vitamins array
  for (int i = 0; i < V; ++i)
    if (vita[i] < vitamins[i])
      return 0;
  return 1;
}

void solve(){
  if (requirements_met()){
    sort(current, current + scoops);
    cout << scoops << " ";
    for (int i = 0; i < scoops; ++i)
      cout << current[i] + 1 << " ";
    cout << endl;
    if (scoops < minscoops || minscoops == 0){
      minscoops = scoops;
      for (int i = 0; i < scoops; ++i)
        solution[i] = current[i];
    }
    // choose the one with smallest feedtype numbers
    if (scoops == minscoops){
      int s = 0;
      int c = 0;
      for (int i = 0; i < scoops; ++i){
        s+=current[i];
        c+=solution[i];
      }
      if (c < s){
        for (int i = 0; i < scoops; ++i)
          solution[i] = current[i];
      }
    }
  }
  for (int i = 0; i < G; ++i)
    if (feed_available(i)){
      current[scoops++] = i;
      solve();
      scoops--;
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
  
  fout << minscoops << " ";
  int i; 
  for (i = 0; i < minscoops - 1; ++i)
    fout << solution[i] + 1 << " ";
  fout << solution[i] + 1 << endl;


  fout.close();
  return 0;
}




