/*
ID: min_j
LANG: C++
TASK: beads
Date: 15/02/2015
Start: 7:45 pm 
End:
*/
#include <iostream>
#include <fstream>
#include <string>
#define MAXN 350
using namespace std;

int main(){
  FILE *fin = fopen("beads.in", "r");
  FILE *fout = fopen("beads.out", "w");
  fout = stdout;
  int n, s, c1, counter, max;
  counter = max = 1;
  c1 = 0;
  char beads[MAXN];
  fscanf(fin, "%d\n%s", &n, beads);
  // Set starting index the first bead of consecutive colors
  for (s = 0; s < n - 1; s++){
    if ((beads[s] == 'r' && beads[s + 1] == 'b') ||
        (beads[s] == 'b' && beads[s + 1] == 'r'))
      break;
  }
  int loop = 0;
  for (int i = (s + 1)%n; loop <= n; ++i && loop++){
    if ((beads[i%n] == 'r' && beads[(i+1)%n] == 'b') ||
        (beads[i%n] == 'b' && beads[(i+1)%n] == 'r') ||
        (loop == n)){
      max = c1 + counter > max ? c1 + counter : max;
      c1 = counter;
      counter = 1;
    }
    else
      counter++;
  }
  fprintf(fout, "%d\n", max - 1);
  fclose(fin); fclose(fout);
  return 0;
}
