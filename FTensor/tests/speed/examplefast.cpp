#include <iostream>
using namespace std;
int main()
{
  double x[3], y[3], n[3];

  y[0] = 0;
  y[1] = 1;
  y[2] = 2;
  x[0] = 2;
  x[1] = 3;
  x[2] = 4;
  n[0] = 5;
  n[1] = 6;
  n[2] = 7;
  for(int i = 1; i < 10000000; i++)
    {
      y[0] = (x[0] + n[0]);
      y[1] = (x[1] + n[1]);
      y[2] = (x[2] + n[2]);

      x[0] = (y[0] - n[0]);
      x[1] = (y[1] - n[1]);
      x[2] = (y[2] - n[2]);

      n[0] = n[0] + (y[0] - x[0]) - (y[0] - x[0]) + (y[0] - x[0])
             - (y[0] - x[0]) + (y[0] - x[0]) - (y[0] - x[0]);
      n[1] = n[1] + (y[1] - x[1]) - (y[1] - x[1]) + (y[1] - x[1])
             - (y[1] - x[1]) + (y[1] - x[1]) - (y[1] - x[1]);
      n[2] = n[2] + (y[2] - x[2]) - (y[2] - x[2]) + (y[2] - x[2])
             - (y[2] - x[2]) + (y[2] - x[2]) - (y[2] - x[2]);
    }
  cout << y[0] << " " << y[1] << " " << y[2] << endl;
}
