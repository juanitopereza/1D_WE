#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void escribe(double *u, double *v, char *filename, int puntos);

int main(){

  char filename[100] = "datosLF.dat";

  int N = 100;
  double t_f = 4.0;

  double dt = t_f/N;

  double *y = (double *) malloc(N*sizeof(double));
  double *t = (double *) malloc(N*sizeof(double));

  y[0] = 1.0;
  t[0] = 0.0;

  y[1] = (1+dt)*y[0];
  t[1] = t[0] + dt;
  int i = 1;

  while (t[i] <= 4.0) {
    t[i+1] = t[i] + dt;
    y[i+1] = 2.0*dt*y[i] + y[i-1];
    i += 1;
  }

  escribe(t,y,filename,N);


  return 0;
}

void escribe(double *u, double *v, char *filename, int puntos){

  FILE *in;
  int i;
  in = fopen(filename,"a");
  for(i=0;i<puntos-1;i++){
    fprintf(in,"%f ", u[i]);
    fprintf(in,"%f\n", v[i]);
  }
  fclose(in);
}
