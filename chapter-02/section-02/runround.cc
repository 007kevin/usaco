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
using namespace std;
unsigned long M;

bool runround(unsigned long n){
  char num[100];
  sprintf(num, "%lu", n);
  int length = strlen(num);
  int len = length;
  int i = 0;
  int sum = 0;
  while (len){
    int nexti = (i+(num[i]-'0'))%length;
    sum += nexti;
    i = nexti;
    len--;
  }
  return sum == length*(length-1)/2;
}

unsigned long getmap(unsigned long n){
  char num[100];
  char imap[100];
  sprintf(num, "%lu", n);
  int i,length = strlen(num);
  for (i = 0; i < length; ++i)
    imap[i] = ((i+num[i]-'0')%length)+'0';
  imap[i] = '\0';
  cout << "NUM: " <<  num << endl;  
  cout << "MAP FROM: ";
  for (int i = 0; i < length; ++i)
    cout << i;
  cout << endl;
  cout << "MAP TO:   " <<  imap << endl << endl;
  return strtoul(imap, NULL, 0);
}

void solve(){
  
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
