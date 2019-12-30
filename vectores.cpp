#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double *reserva(){
  int n_puntos = 3;
  double *array;
  int i;
  if(!(array = (double *) malloc(n_puntos * sizeof(double)))){
    printf("Problema en reserva\n");
    exit(1);
  }
  for(i=0;i<n_puntos;i++){
    array[i] = 0.0;
  }
  return array;
}

void copy(double *origen, double *destino){
  int i;
  for(i=0;i<3;i++){
    destino[i] = origen[i];
  }
}

double *p_escalar(double a, double *x){
  double *y=reserva();
  int i;
  for (i=0; i<3; i++)
    y[i]=a*x[i];
  return y;
}

double *suma_vec(double *x, double *y){
  double *z=reserva();
  int i;
  for(i=0; i<3; i++)
    z[i]=x[i]+y[i];
  return z;
}

double norma(double *x){
  double norma2=0;
  int i;
  for(i=0; i<3; i++)
    norma2+=x[i]*x[i];
  return sqrt(norma2);
}

double *p_cruz(double *x, double *y){
  double *z=reserva();
  z[0]=x[1]*y[2]-x[2]*y[1];
  z[1]=x[2]*y[0]-x[0]*y[2];
  z[2]=x[0]*y[1]-x[1]*y[0];
  return z;
}
