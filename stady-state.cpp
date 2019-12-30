#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

void cond_iniciales(double *v, int N);
void escribe(double *v, double t, int N);
void copia(double *a, double *b, int N);
double maximo(double *a, int N);

int main() {

  double D = 1;
  double s = -1;
  double t = 0;
  double t_fin = 1.0;
  int N;
  double L = 2.0;
  double dx = L/N;
  double dt = (dx*dx)/(2*D);
  double cons = D*dt / (dx*dx);
  double dif = 0;
  double *pasado = new double [N];
  double *presente = new double [N];
  double change = 1000;
  int iteraciones = 0;

  for (size_t i = 1; i < 11; i++) {
    N = i*10;
    change = 1000;
    iteraciones = 0;
    cond_iniciales(pasado,N);

    while (change > 10E-5) {

      iteraciones ++;
      dif = 0;
      // cout << iteraciones << endl;
      for (size_t i = 0; i < N; i++) {
        if ((i == 0) | (i == (N-1))){
          presente[i] = 0.0;
        }
        else {
          presente[i] = pasado[i] + cons * (pasado [i+1] - 2 * pasado [i] + pasado [i-1]) + dt * s;
        }
        // cout << pasado[i] << " , " << presente[i] << endl;
        dif = dif + abs(presente[i]-pasado[i]);
        //cout << "diff: " << dif << endl;
      }
      // cout << "dif: " << dif << endl;
      // cout << "max: " << maximo(presente, N) << endl;
      change = dif/maximo(presente,N);
      // cout << "change: " << change << endl;
      //cout << change << endl;
      //escribe(presente,t,N);
      copia(pasado, presente, N);

    }


    cout << N << " " << iteraciones << endl;

  }


  delete []pasado;
  delete []presente;
  return 0;
}
void cond_iniciales(double *v, int N){
  for (size_t i = 0; i < N; i++) {
    v[i] = 0;
  }
}
void escribe(double *v, double t, int N){
  ofstream file;
  file.open("datos_diff.dat", ios_base::app);
  file << t;
  for (size_t i = 0; i < N-1; i++) {
    file << " " << v[i];
  }
  file << " " << v[-1] << endl;
  file.close();
}
void copia(double *a, double *b, int N){
  for (size_t i = 0; i < N; i++) {
    a[i] = b[i];
  }
}
double maximo(double *a, int N){
  double max = abs(a[0]);
  for (size_t i = 1; i < N; i++) {
    if (abs(a[i]) > max){
      max = abs(a[i]);
    }
  }
  return max;
}
