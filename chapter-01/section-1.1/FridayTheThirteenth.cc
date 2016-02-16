/*
ID: min_j
LANG: C++
TASK: friday
Date: 15/02/2015
Start: 12:35 pm 
End: 2:34 pm
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getDaysOfMonth(int i, int year){
                 // J,  F,  M,  A,  M,  J,  J,  A,  S,  O,  N,  D
  int Month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (i == 1)
    return year % 100 == 0 ? (year % 400 == 0 ? 29 : 28) : (year % 4 == 0 ? 29 : 28);
  else
    return Month[i];
}
int main(){
  FILE *fin = fopen("friday.in", "r");
  FILE *fout = fopen("friday.out", "w");
  /* Each index in the array corresponds to the day 
     of the week starting Monday (i.e index 0) */
  int DayOfWeek[7] = {0};
  int N;
  fscanf(fin, "%d", &N);
  int n = 0;
  int days = 0;
  while (n++ != N){
    for (int i = 0; i < 12; ++i){
      int j;
      int daysofmonth = getDaysOfMonth(i, 1900 + n - 1);
      for (j = 0; j < daysofmonth; ++j)
        if (j == 12) DayOfWeek[(days + j)%7]++;
      days+=daysofmonth;
    }
  }
  int i = 0;
  int j = 5;
  while (i++ != 7){
    fprintf(fout, "%d",DayOfWeek[j%7]);
    i != 7 ? fprintf(fout, " ") : fprintf(fout, "\n");
    j++;
  }

  fclose(fin);
  fclose(fout);
  return 0;
}
