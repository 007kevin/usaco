/*
ID: min_j
LANG: C++
TASK: frac1
Date: 02/04/2015
Analysis:
note ~ to use unique, first sort since it removes all but the first element 
from every consecutive group of equivalent elements

Slick solution using recursion:

We notice that we can start with 0/1 and 1/1 as our ``endpoints'' and 
recursively generate the middle points by adding numerators and denominators.

0/1                                                              1/1
                               1/2
                  1/3                      2/3
        1/4              2/5         3/5                 3/4
    1/5      2/7     3/8    3/7   4/7   5/8       5/7         4/5
    
Each fraction is created from the one up to its right and the one up to its left. 
This idea lends itself easily to a recursion that we cut off when we go too deep.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int n;
FILE *fout;

// print the fractions of denominator <= n between n1/d1 and n2/d2 
void
genfrac(int n1, int d1, int n2, int d2)
{
	if(d1+d2 > n)	// cut off recursion 
		return;

	genfrac(n1,d1, n1+n2,d1+d2);
	fprintf(fout, "%d/%d\n", n1+n2, d1+d2);
	genfrac(n1+n2,d1+d2, n2,d2);
}

void
main(void)
{
	FILE *fin;

	fin = fopen("frac1.in", "r");
	fout = fopen("frac1.out", "w");
	assert(fin != NULL && fout != NULL);

	fscanf(fin, "%d", &n);

	fprintf(fout, "0/1\n");
	genfrac(0,1, 1,1);
	fprintf(fout, "1/1\n");
}
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
struct frac {
  int n, d;
};
vector<frac> reduced;
bool sort_cmp(const frac& a, const frac& b){
  if ((a.n * b.d) == (b.n * a.d))
    return a.d < b.d;
  return (a.n * b.d) < (b.n * a.d);
}
bool uniq_cmp(frac& a, frac& b){
  return (a.n * b.d) == (b.n * a.d);
}
  
int main(){
  ifstream fin("frac1.in");
  ofstream fout("frac1.out");
  fin >> N;
  fin.close();
  for (int i = 1; i <= N; ++i)
    for (int j = 0; j <= i; ++j){
      frac tmp = {j, i};
      reduced.push_back(tmp);
    }
  sort(reduced.begin(), reduced.end(), sort_cmp);
  vector<frac>::iterator it;
  it = unique(reduced.begin(), reduced.end(), uniq_cmp);
  reduced.resize(distance(reduced.begin(), it));

  for (it = reduced.begin(); it != reduced.end(); ++it)
    fout << it->n << "/" << it->d << endl;

  fout.close();
  return 0;
}
