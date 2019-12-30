#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Nx 100
#define Nt 300
#define x_f 2.0
#define t_f 0.3
#define c 1.0

void CondIni(double *x, double dx);
void Evol(double *u_regalo, double *u_historia, double r);
void copy(double *u_new, double *u_old);

int main() {

  double dx = x_f/Nx;
  double dt = t_f/Nt;
  double r = c*dt/dx;

  double *u_historia = malloc(Nx*sizeof(double));
  double *u_regalo = malloc(Nx*sizeof(double));
  double *u_misterio = malloc(Nx*sizeof(double));

  FILE  *datos;
  datos = fopen("datos.csv", "w");

  CondIni(u_historia,dx);
  for (int j = 0; j < Nx; j++) {
    if (j == Nx-1) {
      fprintf(datos,"%lf\n", u_historia[j]);
    } else {
      fprintf(datos,"%lf,", u_historia[j]);
    }
  }
  for (int i = 1; i < Nt; i++) {
    Evol(u_regalo,u_historia,r);
    copy(u_regalo,u_historia);
    for (int j = 0; j < Nx; j++) {

      if (j == Nx-1) {
        fprintf(datos,"%lf\n", u_regalo[j]);
      } else {
        fprintf(datos,"%lf,", u_regalo[j]);
      }
    }
  }
  fclose(datos);

  return 0;
}

void CondIni(double *x, double dx){
  for (int i = 0; i < Nx ; i++) {
    if((i < (int) (0.7/dx)) || (i > (int) (1.2/dx))){
      x[i] = 0.0;
    }
    else {
      x[i] = 2.0;
    }
  }
}
void Evol(double *u_regalo, double *u_historia, double r){
    for (int i = 0; i < Nx; i++) {
      u_regalo[i] = u_historia[i] - r/2.0*(u_historia[i+1] - u_historia[i-1]);
    }
}
void copy(double *u_new, double *u_old){
	for(int i=0;i<Nx;i++){
		u_old[i] = u_new[i];
	}
}
