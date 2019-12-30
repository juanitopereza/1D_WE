#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void initial_cond(double *v, int N);
void copia(double *a, double *b, int N);
void escribe(double *v, int N);

double PI = 3.1415923565;

int main() {
  double L = 1.0;
  double rho = 0.01;
  double T = 40.0;
  double c = sqrt(T/rho);
  double c1 = c;
  double ratio = c*c/(c1*c1);
  int Nx = 101;
  double tmax = 0.1;
  double dx = 1.0/100.0;
  double dt = dx/c1;

  double *pasado = new double [Nx];
  double *presente = new double [Nx];
  double *futuro = new double [Nx];

  initial_cond(pasado, Nx);

  escribe(pasado,Nx);
  presente[0] = 0.0;
  presente[-1] = 0.0;
  for (size_t i = 1; i < Nx-1; i++) {
    presente[i] = pasado[i] + 0.5*ratio*(pasado[i+1] + pasado[i-1] - 2.0*pasado[i]);
  }
  escribe(presente,Nx);

  double t = dt;

  futuro[0] = 0.0;
  futuro[-1] = 0.0;

  while(t < tmax){
    for (size_t i = 1; i < Nx-1; i++) {
      futuro[i] = 2.0*presente[i] - pasado[i] + ratio*(presente[i+1] + presente[i-1] - 2.0*presente[i]);
    }
    escribe(futuro, Nx);

    copia(presente, pasado, Nx);
    copia(futuro, presente, Nx);

    t = t + dt;
  }

  return 0;
}
void initial_cond(double *v, int N){
  for (size_t i = 0; i < N; i++) {
    v[i] = 1E-4 * sin(0.02*PI*i);
  }
}
void escribe(double *v, int N){
  ofstream file;
  file.open("cuerda.dat", fstream::app);
  for (size_t i = 0; i < N; i++) {
    file << v[i]<< " ";
  }
  file << endl;
  file.close();
}
void copia(double *a, double *b, int N){
  for (size_t i = 0; i < N; i++) {
    b[i] = a[i];
  }
}
