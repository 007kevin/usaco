/*
ID: min_j
LANG: C++
TASK: runround
Date: 12/04/2015
Anaylsis:
  81361 maps the indices
  from: 01234
  to:   32040
  whereas the runround number 81362
  maps the indices
  from: 01234
  to:   32041
  therefore all cyclic permutations
  must map to unique indices.
  Since we want the next runround number,
  we need to get the a cyclic permutation
  closest to number M

  Edit - Solved the problem with the simple approach of checking
         every next value to be a rangeround number. As always said:
         "Always try the simplest solution first"

  "The trick to this problem is noticing that since runaround numbers 
   must have unique digits, they must be at most 9 digits long"

*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <climits>
using namespace std;
#define MAXD 11 // max number of digit
unsigned long M;

struct node {
  int d; //digit
  int v; //visited
};

int setup(node *nodes, unsigned long n){
  if (n == 0)
    return 0;
  int i = setup(nodes, n/10);
  nodes[i].d = n%10;
  nodes[i].v = 0;
  return i+1;
}

int getmap(node *nodes, int *imap, unsigned long n){
  int length = setup(nodes, n);
  int i;
  for (i = 0; i < length; ++i)
    imap[i] = ((i+nodes[i].d)%length);
  
  // cout << "NUM: " <<  n << endl;  
  // cout << "MAP FROM: ";
  // for (int i = 0; i < length; ++i)
  //   cout << i;
  // cout << endl;
  
  // cout << "MAP TO:   ";
  // for (int i = 0; i < length; ++i)
  //   cout << imap[i];
  // cout << endl;

  return length;
}

bool runround(unsigned long n){
  node nodes[MAXD];
  int imap[MAXD];
  int length = getmap(nodes,imap,n);
  int sum = 0;
  for (int i = 0; i < length; ++i){
    if (i == imap[i])
      return false;
    for (int j = 0; j < length; ++j){
      if (i!=j&&imap[i]==imap[j])
        return false;
      if (i!=j&&nodes[i].d==nodes[j].d)
        return false;
    }
  }
  int hops = length, i = 0;
  while (hops){
    nodes[i].v++;
    i = (i+nodes[i].d)%length;
    hops--;
  }
  for (int i = 0; i < length; ++i)
    if (nodes[i].v != 1)
      return false;
  return true;
}

int main(){
  ifstream fin("runround.in");
  ofstream fout("runround.out");
  fin>>M;
  fin.close();
  
  M++;
  while (!runround(M))
    M++;
  fout << M << endl;

  fout.close();
  return 0;
}
