#include "vectores.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main() {

  char filename[100] = "datosRK.dat";

  int N = 100;
  double t_f = 4.0;

  double dt = t_f/N;

  double *y = (double *) malloc(N*sizeof(double));
  double *t = (double *) malloc(N*sizeof(double));

  y[0] = 1.0;
  t[0] = 0.0;
  
  return 0;
}

double *f_prima(){

}
