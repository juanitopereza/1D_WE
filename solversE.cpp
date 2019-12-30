#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void escribe(double *u, double *v, char *filename, int puntos);

int main(){

  char filename[100] = "datosE.dat";

  int N = 100;
  double t_f = 4.0;

  double dt = t_f/N;

  double *y = (double *) malloc(N*sizeof(double));
  double *t = (double *) malloc(N*sizeof(double));

  y[0] = 1.0;
  t[0] = 0.0;
  int i = 0;
  while (t[i] <= 4.0) {
    t[i+1] = t[i] + dt;
    y[i+1] = (1+dt)*y[i];
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
