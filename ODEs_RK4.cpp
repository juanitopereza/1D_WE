#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double forzamiento(double omega, double t);

int main(int argc, char const *argv[]) {

  double t_f = 5000;
  double dt = 0.01;
  int N = int(t_f/dt);
  int cols = 3;
  double m = 1000.0;
  double k = 2000.0;
  double gamma = 0.0;
  double omega = 1.0*sqrt(k/m);

  double *t;
  t = new double [N];

  double *u;
  u = new double [N*cols];

  double *v;
  v = new double [N*cols];


  t[0] = 0.0;
  for (int i = 0; i < cols; i++) {
      u[0*cols+i] = 0.0;
      v[0*cols+i] = 0.0;
  }

  double *k_u;
  k_u = new double [4*cols];
  double *k_v;
  k_v = new double [4*cols];

  for (int i = 1; i < N; i++) {
    t[i] = t[i-1] + dt;

    k_v[0*cols+0] = dt*(1.0/m)*(-gamma*v[(i-1)*cols+0] - 2.0*k*u[(i-1)*cols+0] + k*u[(i-1)*cols+1] + forzamiento(omega,t[i-1]));
    k_u[0*cols+0] = dt*v[(i-1)*cols+0];
    k_v[0*cols+1] = dt*(1.0/m)*(-gamma*v[(i-1)*cols+1] + k*u[(i-1)*cols+0] -2.0*k*u[(i-1)*cols+1] + k*u[(i-1)*cols+2]);
    k_u[0*cols+1] = dt*v[(i-1)*cols+1];
    k_v[0*cols+2] = dt*(1.0/m)*(-gamma*v[(i-1)*cols+2] + k*u[(i-1)*cols+1] - k*u[(i-1)*cols+2]);
    k_u[0*cols+2] = dt*v[(i-1)*cols+2];

    k_v[1*cols+0] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+0] + k_v[0*cols+0]/2.0) - 2.0*k*(u[(i-1)*cols+0] + k_u[0*cols+0]/2.0) + k*(u[(i-1)*cols+1] + k_u[0*cols+1]/2.0) + forzamiento(omega,t[i-1]+dt/2.0));
    k_u[1*cols+0] = dt*(v[(i-1)*cols+0] + k_v[0*cols+0]/2.0);
    k_v[1*cols+1] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+1] + k_v[0*cols+1]/2.0) + k*(u[(i-1)*cols+0] + k_u[0*cols+0]/2.0) -2*k*(u[(i-1)*cols+1] + k_u[0*cols+1]/2.0) + k*(u[(i-1)*cols+2] + k_u[0*cols+2]/2.0));
    k_u[1*cols+1] = dt*(v[(i-1)*cols+1] + k_v[0*cols+1]/2.0);
    k_v[1*cols+2] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+2] + k_v[0*cols+2]/2.0) + k*(u[(i-1)*cols+1] + k_u[0*cols+1]/2.0) - k*(u[(i-1)*cols+2] + k_u[0*cols+2]/2.0));
    k_u[1*cols+2] = dt*(v[(i-1)*cols+2] + k_v[0*cols+2]/2.0);

    k_v[2*cols+0] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+0] + k_v[1*cols+0]/2.0) - 2.0*k*(u[(i-1)*cols+0] + k_u[1*cols+0]/2.0) + k*(u[(i-1)*cols+1] + k_u[1*cols+1]/2.0) + forzamiento(omega,t[i-1]+dt/2.0));
    k_u[2*cols+0] = dt*(v[(i-1)*cols+0] + k_v[1*cols+0]/2.0);
    k_v[2*cols+1] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+1] + k_v[1*cols+1]/2.0) + k*(u[(i-1)*cols+0] + k_u[1*cols+0]/2.0) -2*k*(u[(i-1)*cols+1] + k_u[1*cols+1]/2.0) + k*(u[(i-1)*cols+2] + k_u[1*cols+2]/2.0));
    k_u[2*cols+1] = dt*(v[(i-1)*cols+1] + k_v[1*cols+1]/2.0);
    k_v[2*cols+2] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+2] + k_v[1*cols+2]/2.0) + k*(u[(i-1)*cols+1] + k_u[1*cols+1]/2.0) - k*(u[(i-1)*cols+2] + k_u[1*cols+2]/2.0));
    k_u[2*cols+2] = dt*(v[(i-1)*cols+2] + k_v[1*cols+2]/2.0);

    k_v[3*cols+0] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+0] + k_v[2*cols+0]) - 2.0*k*(u[(i-1)*cols+0] + k_u[2*cols+0]) + k*(u[(i-1)*cols+1] + k_u[2*cols+1]) + forzamiento(omega,t[i-1]+dt));
    k_u[3*cols+0] = dt*(v[(i-1)*cols+0] + k_v[2*cols+0]);
    k_v[3*cols+1] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+1] + k_v[2*cols+1]) + k*(u[(i-1)*cols+0] + k_u[2*cols+0]) -2*k*(u[(i-1)*cols+1] + k_u[2*cols+1]) + k*(u[(i-1)*cols+2] + k_u[2*cols+2]));
    k_u[3*cols+1] = dt*(v[(i-1)*cols+1] + k_v[2*cols+1]);
    k_v[3*cols+2] = dt*(1.0/m)*(-gamma*(v[(i-1)*cols+2] + k_v[2*cols+2]) + k*(u[(i-1)*cols+1] + k_u[2*cols+1]) - k*(u[(i-1)*cols+2] + k_u[2*cols+2]));
    k_u[3*cols+2] = dt*(v[(i-1)*cols+2] + k_v[2*cols+2]);

    for (int j = 0; j < cols; j++) {
      v[i*cols+j] = v[(i-1)*cols+j] + (1.0/6.0)*(k_v[0*cols+j] + 2.0*k_v[1*cols+j] + 2.0*k_v[2*cols+j] + k_v[3*cols+j]);
      u[i*cols+j] = u[(i-1)*cols+j] + (1.0/6.0)*(k_u[0*cols+j] + 2.0*k_u[1*cols+j] + 2.0*k_u[2*cols+j] + k_u[3*cols+j]);
    }

  }

  delete[] k_v;
  delete[] k_u;


  ofstream file1;
  file1.open("posiciones.txt");
  ofstream file2;
  file2.open("veocidades.txt");
  for(int i=0;i<N;i++){
    file1 << t[i] <<" " << u[i*cols+0] <<" " << u[i*cols+1] <<" " << u[i*cols+2] << endl;
    file2 << t[i] <<" " << v[i*cols+0] <<" " << v[i*cols+1] <<" " << v[i*cols+2] << endl;
  }
  file1.close();
  file2.close();

  delete[] u;
  delete[] v;
  delete[] t;

  return 0;
}

double forzamiento(double omega, double t){
  return sin(omega*t);
}
