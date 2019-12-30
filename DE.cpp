#include<iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

void cond_iniciales(float *v, int N);
void escribe(float *v, float t, int N);
void copia(float *a, float *b, int N);

int main() {

  float D = 1;
  float s = 1;
  float t = 0;
  float t_fin = 1.0;
  int N = 30;
  float L = 2.0;
  float dx = L/N;
  float dt = (dx*dx)/(2*D);
  float cons = D*dt / (dx*dx);

  float *pasado = new float [N];
  float *presente = new float [N];

  cond_iniciales(pasado,N);
  escribe(pasado, t, N);

  while (t < t_fin) {

    t = t + dt;
    for (size_t i = 0; i < N; i++) {
      if (i == 0 | i == (N-1)){
        presente[i] = 0.0;
      }
      else {
        presente[i] = pasado[i] + cons * (pasado [i+1] - 2 * pasado [i] + pasado [i-1]) + dt * s;
      }
    }

    escribe(presente,t,N);
    copia(pasado, presente, N);
  }


  delete []pasado;
  delete []presente;
  return 0;
}
void cond_iniciales(float *v, int N){
  for (size_t i = 0; i < N; i++) {
    v[i] = 0;
  }
}
void escribe(float *v, float t, int N){
  ofstream file;
  file.open("datos_diff.dat", ios_base::app);
  file << t;
  for (size_t i = 0; i < N-1; i++) {
    file << " " << v[i];
  }
  file << " " << v[-1] << endl;
  file.close();
}
void copia(float *a, float *b, int N){
  for (size_t i = 0; i < N; i++) {
    a[i] = b[i];
  }
}
