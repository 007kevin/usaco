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

  Will we ever need to increase the number of digits to get to the
  next rangeround number? => no because 9, 99 , 99...9 are all rangeround
  numbers

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

unsigned long getmap(int *imap, unsigned long n){
  node nodes[MAXD];
  int length = setup(nodes, n);
  int i;
  for (i = 0; i < length; ++i)
    imap[i] = ((i+nodes[i].d)%length);
  cout << "NUM: " <<  n << endl;  
  cout << "MAP FROM: ";
  for (int i = 0; i < length; ++i)
    cout << i;
  cout << endl;
  
  cout << "MAP TO:   ";
  for (int i = 0; i < length; ++i)
    cout << imap[i];
  cout << endl;

  length;
}

bool runround(unsigned long n){
  int imap[MAXD];
  int length = getmap(imap, n);
  return 1;
}

int main(){
  ifstream fin("runround.in");
  ofstream fout("runround.out");
  fin>>M;
  fin.close();
  // M++;
  // while (!runround(M))
  //   M++;
  // cout << M << endl;
  runround(81362);


  fout.close();
  return 0;
}
