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

bool ispalindrome(int n){
  char num[100];
  sprintf(num, "%d", n);
  int i = 0;
  int j = strlen(num) - 1;
  while (i < j){
    if (num[i] != num[j])
      return false;
    i++; j--;
  }
  return true;
}

int main(){
  cout << ispalindrome(100101) << endl;
  return 0;
}
