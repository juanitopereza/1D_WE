#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

//Implementacion de metodo Runge Kutta//

double forzamiento(double t, double omega){
		return sin(omega*t);
		}

int main(){

	double tot_t = 10;
	double dt = 0.1;
	int n = int (tot_t/dt);
	double m = 1000;
	double gamma = 0;
	double k = 2000;
	double omega = sqrt(k/m);
	double *t;
	t = new double [n];

	double *u1;
	u1 = new double [n];
	double *u2;
	u2 = new double [n];
	double *u3;
	u3 = new double [n];
	double *v1;
	v1 = new double [n];
	double *v2;
	v2 = new double [n];
	double *v3;
	v3 = new double [n];
	u1[0]=0,u2[0]=0,u3[0]=0;
	v1[0]=0,v2[0]=0,v3[0]=0;
	t[0]=0;
	double k1,k2,k3,k4,k5,k6,k7,k8,k9,k10,k11,k12,k13,k14,k15,k16,k17,k18,k19,k20,k21,k22,k23,k24;


	for(int i=1; i<=n; i++){
		t[i]= t[i-1]+dt;
		k1 = dt*(1/m)*(-gamma*v1[i-1]-2*k*u1[i-1]+k*u2[i-1]+ forzamiento(t[i-1],omega));
		k2 = dt*(1/m)*(-gamma*v2[i-1]+k*u1[i-1]-2*k*u2[i-1]+ k*u3[i-1]);
		k3 = dt*(1/m)*(-gamma*v3[i-1]+k*u2[i-1]-k*u3[i-1]);
		k4 = dt*v1[i-1];
		k5 = dt*v2[i-1];
		k6 = dt*v3[i-1];
		k7 = dt*(1/m)*(-gamma*(v1[i-1]+k1/2)-2*k*(u1[i-1]+k4/2)+k*(u2[i-1]+k5/2)+ forzamiento((t[i-1]+dt/2),omega));
		k8 = dt*(1/m)*(-gamma*(v2[i-1]+k2/2)+k*(u1[i-1]+k4/2)-2*k*(u2[i-1]+k5/2)+ k*(u3[i-1]+k6/2));
		k9 = dt*(1/m)*(-gamma*(v3[i-1]+k3/2)+k*(u2[i-1]+k5/2)-k*(u3[i-1]+k6/2));
		k10 = dt*(v1[i-1]+k1/2);
		k11 = dt*(v2[i-1]+k2/2);
		k12 = dt*(v3[i-1]+k3/2);
		k13 = dt*(1/m)*(-gamma*(v1[i-1]+k7/3)-2*k*(u1[i-1]+k10/2)+k*(u2[i-1]+k11/2)+ forzamiento((t[i-1]+dt/2),omega));
		k14 = dt*(1/m)*(-gamma*(v2[i-1]+k8/3)+k*(u1[i-1]+k10/2)-2*k*(u2[i-1]+k11/2)+ k*(u3[i-1]+k12/2));
		k15 = dt*(1/m)*(-gamma*(v3[i-1]+k9/3)+k*(u2[i-1]+k11/2)-k*(u3[i-1]+k12/2));
		k16 = dt*(v1[i-1]+k7/3);
		k17 = dt*(v2[i-1]+k8/3);
		k18 = dt*(v3[i-1]+k9/3);
		k19 = dt*(1/m)*(-gamma*(v1[i-1]+k13)-2*k*(u1[i-1]+k16)+k*(u2[i-1]+k17)+ forzamiento((t[i-1]+dt),omega));
		k20 = dt*(1/m)*(-gamma*(v2[i-1]+k14)+k*(u1[i-1]+k16)-2*k*(u2[i-1]+k17)+ k*(u3[i-1]+k18));
		k21 = dt*(1/m)*(-gamma*(v3[i-1]+k15)+k*(u2[i-1]+k17)-k*(u3[i-1]+k18));
		k22 = dt*(v1[i-1]+k13);
		k23 = dt*(v2[i-1]+k14);
		k24 = dt*(v3[i-1]+k15);



		u1[i] = u1[i-1]+(1.0/6)*(k4+2*k10+2*k16+k22);
		u2[i] = u2[i-1]+(1.0/6)*(k5+2*k11+2*k17+k23);
		u3[i] = u3[i-1]+(1.0/6)*(k6+2*k12+2*k18+k24);
		v1[i] = v1[i-1]+(1.0/6)*(k1+2*k7+2*k13+k19);
		v2[i] = v2[i-1]+(1.0/6)*(k2+2*k8+2*k14+k20);
		v3[i] = v3[i-1]+(1.0/6)*(k3+2*k9+2*k15+k21);
		}
	//Genero archivo con datos para poder hacer plots en python//
	ofstream file;
	file.open("datos.dat");
	for(int j=0; j<=n; j++){
		file << t[j] <<" "<< u1[j] <<" "<< u2[j] <<" "<< u3[j] <<" "<< v1[j] <<" "<< v2[j] <<" "<< v3[j] <<endl;
		}
	file.close();

	return 0;
	}
