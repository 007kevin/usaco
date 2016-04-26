/*
  ID: min_j
  LANG: C++
  TASK: ttwo
  Date: 25/04/2015
  Anaylsis:
  There are only 100 places where the cows can meet, and only 4
  directions they can face, leaving us with 400*400 = 160000 different
  configurations for FJ and COWS. If they are to meet, they will meet
  within the 160000 configurations else is an infinite loop. 
*/
#include <stdio.h>

typedef struct {
  int s[2],c[2];
  char d;
} obj;
obj FJ, COWS;

char grid[10][11];

void rotate(obj *o){
  switch(o->d){
  case 'n':
    o->d = 'e'; break;
  case 'e':
    o->d = 's'; break;
  case 's':
    o->d = 'w'; break;
  case 'w':
    o->d = 'n'; break;
  }
}

void move(obj *o){
  switch(o->d){
  case 'n':
    if (o->c[0] > 0 && grid[o->c[0]-1][o->c[1]] != '*')
      o->c[0]--;
    else
      rotate(o);
    break;
  case 'e':
    if (o->c[1] < 9 && grid[o->c[0]][o->c[1]+1] != '*')
      o->c[1]++;
    else
      rotate(o);
    break;
  case 's':
    if (o->c[0] < 9 && grid[o->c[0]+1][o->c[1]] != '*')
      o->c[0]++;
    else
      rotate(o);
    break;
  case 'w':
    if (o->c[1] > 0 && grid[o->c[0]][o->c[1]-1] != '*')
      o->c[1]--;
    else
      rotate(o);
    break;
  }
}

int tick(){
  int count = 0;
  while (1){

    // printf("FJ: %d %d %c\n", FJ.c[0],FJ.c[1],FJ.d); 
    // printf("COWS: %d %d %c\n", COWS.c[0],COWS.c[1],COWS.d);
    // printf("----------------- %d\n", count);
    
    if (count != 0 &&
        FJ.s[0] == FJ.c[0] &&
        FJ.s[1] == FJ.c[1] &&
        COWS.s[0] == COWS.c[0] &&
        COWS.s[1] == COWS.c[1] &&
        FJ.d == 'n' && COWS.d == 'n')
      return 0;
    if (count == 160000)
      return 0;
    if (FJ.c[0] == COWS.c[0] &&
        FJ.c[1] == COWS.c[1])
      return count;
    move(&FJ);
    move(&COWS);
    count++;
  }
}

int main(){
  FILE *fin = fopen("ttwo.in", "r");
  FILE *fout = fopen("ttwo.out", "w");
  int i = 0;
  while (i < 10)
    fscanf(fin,"%s",grid[i++]);
  fclose(fin);
  
  // get position of fj and cows
  for (int i = 0; i < 10; ++i)
    for (int j =0 ; j < 10; ++j){
      if (grid[i][j] == 'F'){
        FJ.s[0] = i; FJ.s[1] = j;
        FJ.c[0] = i; FJ.c[1] = j;
        FJ.d = 'n';
      }
      if (grid[i][j] == 'C'){
        COWS.s[0] = i; COWS.s[1] = j;
        COWS.c[0] = i; COWS.c[1] = j;
        COWS.d = 'n';
      }
    }

        
  fprintf(fout, "%d\n", tick());
  fclose(fout);
  
  // for (int i =0 ; i < 10; ++i)
  //   printf("%s\n", grid[i]);
  
  return 0;
}
