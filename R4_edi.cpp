#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double forzamiento(double omega, double t);

int main(int argc, char const *argv[]) {

  double t_f = 5000;
  double dt = 0.01;
  int N = int(t_f/dt);
  double m = 1000.0;
  double k = 2000.0;
  double gamma = 0.0;
  double omega = 1.0*sqrt(k/m);

  double *t;
  t = new double [N];

  double *u1;
  u1 = new double [N];
  double *u2;
  u2 = new double [N];
  double *u3;
  u3 = new double [N];

  double *v1;
  v1 = new double [N];
  double *v2;
  v2 = new double [N];
  double *v3;
  v3 = new double [N];

  t[0] = 0.0;
  u1[0] = 0.0;
  u2[0] = 0.0;
  u3[0] = 0.0;
  v1[0] = 0.0;
  v2[0] = 0.0;
  v3[0] = 0.0;

  double k1_1, k2_1, k3_1, k4_1;
  double L1_1, L2_1, L3_1, L4_1;

  double k1_2, k2_2, k3_2, k4_2;
  double L1_2, L2_2, L3_2, L4_2;

  double k1_3, k2_3, k3_3, k4_3;
  double L1_3, L2_3, L3_3, L4_3;


  for (int i = 1; i < N; i++) {
    t[i] = t[i-1] + dt;

    k1_1 = dt*(1.0/m)*(-gamma*v1[i-1] - 2*k*u1[i-1] + k*u2[i-1] + forzamiento(omega,t[i-1]));
    L1_1 = dt*v1[i-1];
    k1_2 = dt*(1.0/m)*(-gamma*v2[i-1] + k*u1[i-1] -2*k*u2[i-1] + k*u3[i-1]);
    L1_2 = dt*v2[i-1];
    k1_3 = dt*(1.0/m)*(-gamma*v3[i-1] + k*u2[i-1] - k*u3[i-1]);
    L1_3 = dt*v3[i-1];

    k2_1 = dt*(1.0/m)*(-gamma*(v1[i-1] + k1_1/2.0) - 2*k*(u1[i-1] + L1_1/2.0) + k*(u2[i-1] + L1_2/2.0) + forzamiento(omega,t[i-1]+dt/2.0));
    L2_1 = dt*(v1[i-1] + k1_1/2.0);
    k2_2 = dt*(1.0/m)*(-gamma*(v2[i-1] + k1_2/2.0) + k*(u1[i-1] + L1_1/2.0) -2*k*(u2[i-1] + L1_2/2.0) + k*(u3[i-1] + L1_3/2.0));
    L2_2 = dt*(v2[i-1] + k1_2/2.0);
    k2_3 = dt*(1.0/m)*(-gamma*(v3[i-1] + k1_3/2.0) + k*(u2[i-1] + L1_2/2.0) - k*(u3[i-1] + L1_3/2.0));
    L2_3 = dt*(v3[i-1] + k1_3/2.0);

    k3_1 = dt*(1.0/m)*(-gamma*(v1[i-1] + k2_1/2.0) - 2*k*(u1[i-1] + L2_1/2.0) + k*(u2[i-1] + L2_2/2.0) + forzamiento(omega,t[i-1]+dt/2.0));
    L3_1 = dt*(v1[i-1] + k2_1/2.0);
    k3_2 = dt*(1.0/m)*(-gamma*(v2[i-1] + k2_2/2.0) + k*(u1[i-1] + L2_1/2.0) -2*k*(u2[i-1] + L2_2/2.0) + k*(u3[i-1] + L2_3/2.0));
    L3_2 = dt*(v2[i-1] + k2_2/2.0);
    k3_3 = dt*(1.0/m)*(-gamma*(v3[i-1] + k2_3/2.0) + k*(u2[i-1] + L2_2/2.0) - k*(u3[i-1] + L2_3/2.0));
    L3_3 = dt*(v3[i-1] + k2_3/2.0);

    k3_1 = dt*(1.0/m)*(-gamma*(v1[i-1] + k3_1) - 2*k*(u1[i-1] + L3_1) + k*(u2[i-1] + L3_2) + forzamiento(omega,t[i-1]+dt));
    L3_1 = dt*(v1[i-1] + k3_1);
    k3_2 = dt*(1.0/m)*(-gamma*(v2[i-1] + k3_2) + k*(u1[i-1] + L3_1) -2*k*(u2[i-1] + L3_2) + k*(u3[i-1] + L3_3));
    L3_2 = dt*(v2[i-1] + k3_2);
    k3_3 = dt*(1.0/m)*(-gamma*(v3[i-1] + k3_3) + k*(u2[i-1] + L3_2) - k*(u3[i-1] + L3_3));
    L3_3 = dt*(v3[i-1] + k3_3);

    v1[i] = v1[i-1] + (1.0/6.0)*(k1_1 + 2*k2_1 + 2*k3_1 + k4_1);
    v2[i] = v2[i-1] + (1.0/6.0)*(k1_2 + 2*k2_2 + 2*k3_2 + k4_2);
    v3[i] = v3[i-1] + (1.0/6.0)*(k1_3 + 2*k2_3 + 2*k3_3 + k4_3);

    u1[i] = u1[i-1] + (1.0/6.0)*(L1_1 + 2*L2_1 + 2*L3_1 + L4_1);
    u2[i] = u2[i-1] + (1.0/6.0)*(L1_2 + 2*L2_2 + 2*L3_2 + L4_2);
    u3[i] = u3[i-1] + (1.0/6.0)*(L1_3 + 2*L2_3 + 2*L3_3 + L4_3);
  }


  ofstream file1;
  file1.open("posiciones.txt");
  ofstream file2;
  file2.open("veocidades.txt");
  for(int i=0;i<N;i++){
    file1 << t[i] <<" " << u1[i] <<" " << u2[i] <<" " << u3[i] << endl;
    file2 << t[i] <<" " << v1[i] <<" " << v2[i] <<" " << v3[i] << endl;
  }
  file1.close();
  file2.close();

  delete[] t;
  delete[] u1;
  delete[] u2;
  delete[] u3;
  delete[] v1;
  delete[] v2;
  delete[] v3;

  return 0;
}

double forzamiento(double omega, double t){
  return sin(omega*t);
}
