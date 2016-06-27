/*
ID: min_j
LANG: C++
TASK: fence9
Date: 26/06/2016
Anaylsis:
  Note: 
  - By making use of a reference point we know 
    to be in the triangle, we take the cross products
    of each corner of the triangle and make sure the
    testing point also points in the same direction.
  
*/
#include <iostream>
#include <fstream>
#include <cassert>
#define max(a,b) ((a) > (b) ? a : b)
using namespace std;
double N,M,P;
long long cows;
struct point {
  double x,y,z;
  point(double x1, double y1, double z1){
    x = x1, y = y1, z = z1;
  }
  point operator-(point r){
    return point(x-r.x,y-r.y,z-r.z);
  }
};
point crossproduct(point p1, point p2){
  return point(p1.y*p2.z-p1.z*p2.y,
               p1.z*p2.x-p1.x*p2.z,
               p1.x*p2.y-p1.y*p2.x);
}

bool inTriangle(point a, point b, point c, point p){
  point ref = point((a.x+b.x+c.x)/3,
                    (a.y+b.y+c.y)/3,
                    0);
  point bara = crossproduct(b-a,ref-a);
  point cara = crossproduct(c-a,ref-a);
  point bcrc = crossproduct(b-c,ref-c);
  point bapa = crossproduct(b-a,p-a);
  point capa = crossproduct(c-a,p-a);
  point bcpc = crossproduct(b-c,p-c);
  // if z == 0, then point is along wire fence
  if (bapa.z == 0 || capa.z == 0 || bcpc.z == 0)
    return false;
  if (bara.z < 0 == bapa.z < 0 &&
      cara.z < 0 == capa.z < 0 &&
      bcrc.z < 0 == bcpc.z < 0)
    return true;
  return false;
}

int main(){
  ifstream fin("fence9.in");
  ofstream fout("fence9.out");
  assert(fin.is_open());
  assert(fout.is_open());
  fin>>N>>M>>P;
  point a = point(0,0,0);
  point b = point(N,M,0);
  point c = point(P,0,0);
  
  // We start from the height where there is at least
  // 1 valid lattice to keep r > l in the while loops
  int x,start;
  for (start = M; start >= 0; --start){
    bool flag = false;
    for (x = 0; x <= max(N,P); ++x)
      if (inTriangle(a,b,c,point(x,start,0))){
        flag = true;
        break;
      }
    if (flag) break;
  }
  cout << x << " " << start << endl;
  int l = x;
  int r = x;
  for (int y = start; y > 0; --y){
    cout << l << " " << r << endl;
    
    while (inTriangle(a,b,c,point(r,y,0))) r++;
    while (!inTriangle(a,b,c,point(r,y,0))) r--;
    l = r;
    while (inTriangle(a,b,c,point(l,y,0))) l--;
    while (!inTriangle(a,b,c,point(l,y,0))) l++;
    cows += (r-l+1);
  }
  fout << cows << endl;
  fout.close();
  return 0;
}
