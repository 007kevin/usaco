/*
ID: min_j
LANG: C++
TASK: preface
Date: 07/04/2015
Analysis:
*/
#include <iostream>
#include <fstream>
using namespace std;
int N;

int NUMERALS[256];

void roman(char *s, int n){
  s[0] = '\0';
  while(n){
    if (n-1000 >= 0){
      //sprintf(s, "%sM", s);
      n -= 1000;
      NUMERALS['M']++; 
    }
    else if (n%1000 >= 900){
      //sprintf(s, "%sCM", s);
      n -= 900;
      NUMERALS['C']++;
      NUMERALS['M']++; 
    }
    else if (n-500 >= 0){
      //sprintf(s, "%sD", s);
      n -= 500;
      NUMERALS['D']++;       
    }
    else if (n%500 >= 400){
      //sprintf(s, "%sCD", s);
      n -= 400;
      NUMERALS['C']++;
      NUMERALS['D']++;       
    }
    else if (n-100 >= 0){
      //sprintf(s, "%sC", s);
      n -= 100;
      NUMERALS['C']++;       
    }
    else if (n%100 >= 90){
      //sprintf(s, "%sXC", s);
      n -= 90;
      NUMERALS['X']++;
      NUMERALS['C']++;       
    }
    else if (n-50 >= 0){
      //sprintf(s, "%sL", s);
      n -= 50;
      NUMERALS['L']++; 
    }
    else if (n%50 >= 40){
      //sprintf(s, "%sXL", s);
      n -= 40;
      NUMERALS['X']++;
      NUMERALS['L']++;       
    }
    else if (n-10 >= 0){
      //sprintf(s, "%sX", s);
      n -= 10;
      NUMERALS['X']++;       
    }
    else if (n%10 >= 9){
      //sprintf(s, "%sIX", s);
      n -= 9;
      NUMERALS['I']++;
      NUMERALS['X']++;       
    }
    else if (n-5 >= 0){
      //sprintf(s, "%sV", s);
      n -= 5;
      NUMERALS['V']++;       
    }
    else if (n%5 >= 4){
      //sprintf(s, "%sIV", s);
      n -= 4;
      NUMERALS['I']++;
      NUMERALS['V']++;       
    }
    else{
      //sprintf(s, "%sI", s);
      n -= 1;
      NUMERALS['I']++;       
    }
  }
}

int main(){
  FILE *fin = fopen("preface.in", "r");
  FILE *fout = fopen("preface.out", "w");
  fscanf(fin, "%d",& N);
  fclose(fin);


  char buf[100];
  for (int i = 1; i <= N; ++i){
    roman(buf, i);
    //fprintf(fout, "%s\n", buf);
  }
  if (NUMERALS['I'])
    fprintf(fout, "I %d\n", NUMERALS['I']);
  if (NUMERALS['V'])
    fprintf(fout, "V %d\n", NUMERALS['V']);
  if (NUMERALS['X'])
    fprintf(fout, "X %d\n", NUMERALS['X']);
  if (NUMERALS['L'])
    fprintf(fout, "L %d\n", NUMERALS['L']);
  if (NUMERALS['C'])
    fprintf(fout, "C %d\n", NUMERALS['C']);
  if (NUMERALS['D'])
    fprintf(fout, "D %d\n", NUMERALS['D']);
  if (NUMERALS['M'])
    fprintf(fout, "M %d\n", NUMERALS['M']);
    
  fclose(fout);
  return 0;
}
