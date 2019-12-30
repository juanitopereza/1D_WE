#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// variable constantes globales
const double K = 100;
const double M = 2;
const double GAMMA = 0.2;
const double DeltaT = 0.01;

// declaracion de funciones
double f0(double t, double y0, double y1); // derivada de y0
double f1(double t, double y0, double y1, double lambda);
void rk4(double t, double h, double & y0, double & y1, double lambda); // metodo de runge kutta 4 orden

int main(void)
{
  double x, v, time;
  double *lambda = new double [6];

  lambda[0] = 1;
  lambda[1] = 2;
  lambda[2] = 3;
  lambda[3] = 1/2;
  lambda[4] = 3/2;
  lambda[5] = 4;

  for (size_t i = 0; i < 6; i++) {
    ofstream file;
    file.open("data_fr_"+to_string(i)+".dat");
    x = 1;
    v = 0;
    for(time = 0; time <= 1000*DeltaT; time += DeltaT) {
      file << time << " " << x << " " << v << endl;
      rk4(time, DeltaT, x, v, lambda[i]);
    }
    file.close();
  }



  return 0;
}
double f0(double t, double y0, double y1)
{
  return y1;
}

double f1(double t, double y0, double y1, double lambda)
{
  return (-K/M)*pow(y0, lambda) - (GAMMA/M)*y1;
}

void rk4(double t, double h, double & y0, double & y1, double lambda) // metodo de runge kutta 4 orden
{
  double k10, k11, k20, k21, k30, k31, k40, k41;
  k10 = h*f0(t, y0, y1);
  k11 = h*f1(t, y0, y1, lambda);
  k20 = h*f0(t+h/2, y0 + k10/2, y1 + k11/2);
  k21 = h*f1(t+h/2, y0 + k10/2, y1 + k11/2, lambda);
  k30 = h*f0(t+h/2, y0 + k20/2, y1 + k21/2);
  k31 = h*f1(t+h/2, y0 + k20/2, y1 + k21/2, lambda);
  k40 = h*f0(t + h, y0 + k30, y1 + k31);
  k41 = h*f1(t + h, y0 + k30, y1 + k31, lambda);

  y0 = y0 + (1.0/6.0)*(k10 + 2*k20 + 2*k30 + k40);
  y1 = y1 + (1.0/6.0)*(k11 + 2*k21 + 2*k31 + k41);
}
