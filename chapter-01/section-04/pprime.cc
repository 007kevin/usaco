/*
ID: min_j
LANG: C++
TASK: pprime
Date: 21/03/2015
*/
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
unsigned long a, b;

bool ispalindrome(unsigned long n){
  char num[100];
  sprintf(num, "%lu", n);
  int i = 0;
  int j = strlen(num) - 1;
  while (i < j){
    if (num[i] != num[j])
      return false;
    i++; j--;
  }
  return true;
}

bool isprime(unsigned long n){
  if (n == 2)
    return true;
  if (n == 3)
    return true;
  if (n % 2 == 0)
    return false;
  if (n % 3 == 0)
    return false;

  int i = 5;
  int w = 2;
  while (i * i <= n){
    if (n % i == 0)
      return false;
    i+=w;
    w = 6 - w;
  }
  return true;
}

int numdigits(unsigned long n){
  char num[100];
  sprintf(num, "%lu", n);
  return strlen(num);
}

int main(){
  ifstream fin("pprime.in");
  ofstream fout("pprime.out");
  fin>>a>>b;
  fin.close();

  unsigned long i = a;
  if (a % 2 == 0)
    i = a - 1;
  for (i; i <= b && i < 10000000; i+=2){
    int nd = numdigits(i);
    if (i > 11 && nd%2 == 0){
      switch(nd){
      case 2:
        i = 101;
        break;
      case 4:
        i = 10001;
        break;
      case 6:
        i = 1000001;
        break;
      }
    }

    if (ispalindrome(i) && isprime(i))
      fout << i << endl;
  }

  fout.close();
    
  return 0;
}
