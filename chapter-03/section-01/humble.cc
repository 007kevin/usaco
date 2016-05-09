/*
ID: min_jn
LANG: C++
TASK: humble
Date: 07/05/2015
Anaylsis:
  Use a sorted queue to generate the numbers of S
  in increasing order.
  Note - Even with a min priority queue, this algorithm fails
         in run time with the following data:
     
100 100000
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 
71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 
149 151 157 163 167 173 179 181 191 193 197 199 211 223 
227 229 233 239 241 251 257 263 269 271 277 281 283 293 
307 311 313 317 331 337 347 349 353 359 367 373 379 383
389 397 401 409 419 421 431 433 439 443 449 457 461 463 
467 479 487 491 499 503 509 521 523 541

The sorting of priority queue may be what is causing the problem.
We could eliminate sorted insertion by somehow creating
S in sequential order.

Solution Correct:
  By adding the break statement to the dup loop and
  changing from iostream to stdio,  I was able to 
  reduce runtime just enough to pass.
*/
#include <stdio.h>
#include <queue>
using namespace std;
#define MAXK 100
int subS[MAXK+1];
int N,K;
int counter;
priority_queue<long long,
               vector<long long>,
               greater<long long> > S;

int main(){
  FILE *fin = fopen("humble.in", "r");
  FILE *fout = fopen("humble.out", "w");
  fscanf(fin,"%d %d",&K,&N);
  for (int i = 0; i < K; ++i){
    fscanf(fin,"%d",subS+i);
  }
  fclose(fin);
  S.push(1); // Set 'base case'
  while (true){
    long long number = S.top();
    S.pop();
    if (number != 1)
      if (++counter == N){
        fprintf(fout,"%lld\n",number);
        break;
      }
    for (int i = 0; i < K; ++i){
      bool dup = false;          
      for (int j = 0; j < i; ++j) 
        if (number%subS[j] == 0){
          dup = true;
          break;
        }
      if (dup == false)
        S.push(number*subS[i]);
      
    }
  }
  fclose(fout);
  return 0;
}
