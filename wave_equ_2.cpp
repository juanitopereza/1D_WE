#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void cond_ini(double u[], double x[], int N);
void copia(double a[], double b[], int N);

int main(int argc, char const *argv[]){
  double c =1.0;
  double L = 1.0;
  int n_t = 500;
  double dt = 0.0005;
  double t_fin = n_t*dt;
  // int n_t = int(t_fin/dt);
  int N = 1000;
  double dx = L/N;
  double r = c*dt/dx;

  double x[N];
  double u_ini[N];
  double u_historia[N];
  double u_regalo[N];
  double u_misterio[N];

  x[0] = 0.0;
  for (int i = 1; i < N; i++) {
    x[i] = x[i-1] + dx;
  }

  cond_ini(u_ini, x, N);

  ofstream file;
  file.open("inicial.txt");
  for(int i=0;i<N;i++){
    file << x[i] <<" " << u_ini[i] << endl;
  }
  file.close();

  u_misterio[0] = 0.0;
  u_misterio[N-1] = 0.0;

  for (int i = 1; i < N; i++) {
    u_misterio[i] = u_ini[i] + (pow(r,2)/2.0)*(u_ini[i+1] + u_ini[i-1] -2.0*u_ini[i]);
  }

  copia(u_ini, u_historia, N);
  copia(u_misterio,u_regalo, N);

  ofstream file2;
  file2.open("datos.txt", fstream::app);
  file2 << 0 << " ";
  for(int i=0;i<N;i++){
    file2 << x[i] <<" ";
  }
  file2 << endl;

  double t =0.0;
  while (t < t_fin) {
    for (int k = 1; k < N-1; k++) {
      u_misterio[k] = (2.0*(1.0-r*r))*u_regalo[k] - u_historia[k] + (r*r)*(u_regalo[k+1] + u_regalo[k-1]);
    }
    copia(u_regalo,u_historia, N);
    copia(u_misterio,u_regalo, N);
    file2 << t << " ";
    for(int j=0;j<N;j++){
    file2 << u_regalo[j] <<" ";
    }
    file2 << endl;
    t += dt;
    cout << "t = "<< t << '\n';
  }

  file2.close();

  ofstream file3;
  file3.open("final.txt");
  for(int i=0;i<N;i++){
    file3 << x[i] <<" " << u_regalo[i] << endl;
  }
  file3.close();

  return 0;
}

void cond_ini(double u[], double x[], int N){
  u[0] = 0.0;
  u[N-1] = 0.0;
  for (int i = 1; i < N-1; i++) {
    u[i] = exp(-pow((x[i] - 0.3), 2)/0.01);
  }
}

void copia(double a[], double b[], int N){
  for (int i = 0; i < N; i++) {
    b[i] = a[i];
  }
}
