#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

const double g = 9.8;
double PI = 3.141592;

int main() {

  double t_final = 10;
  double dt = 0.01;
  double v0 = 30;
  double theta = 30;
  double b = 5; // Coef de rozamiento con el aire

  double t = 0;
  double x = 0;
  double y = 0;
  double vx = v0*sin(theta*PI/180.0);
  double vy = v0*cos(theta*PI/180.0);
  double ax = 0;
  double ay = 0;

  double a_temp = 0;

  ofstream file;
  file.open("MUA.dat");

  file << t << " " << x << " " << y << " " << vx << " " << vy << " " << endl;

  // Esto es el Leapfrog
  while (t < t_final) {
    t = t +dt;
    x = x + vx*dt + 0.5*ax*dt*dt;
    a_temp = -b*vx; // esto es porque necesitamos la aceleracion (d²x/dt² = F(x,y,vx,vy,t)) en el "futuro" y en el "pasado"
    vx = vx + 0.5*(ax + a_temp)*dt;
    ax = a_temp;

    y = y + vy*dt + 0.5*ay*dt*dt;
    a_temp = -g -b*vy;
    vy = vy + 0.5*(ay + a_temp)*dt;
    ay = a_temp;

    if (y < 0) {
      break;
    }

    file << t << " " << x << " " << y << " " << vx << " " << vy << " " << endl;

  }

  file.close();
  return 0;
}
