#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float *reserva(){
  int n_puntos = 3;
  float *array;
  int i;
  if(!(array = malloc(n_puntos * sizeof(float)))){
    printf("Problema en reserva\n");
    exit(1);
  }
  for(i=0;i<n_puntos;i++){
    array[i] = 0.0;
  }
  return array;
}

void copy(float *origen, float *destino){
  int i;
  for(i=0;i<3;i++){
    destino[i] = origen[i];
  }
}

float *p_escalar(float a, float *x){
  float *y=reserva();
  int i;
  for (i=0; i<3; i++)
    y[i]=a*x[i];
  return y;
}

float *suma_vec(float *x, float *y){
  float *z=reserva();
  int i;
  for(i=0; i<3; i++)
    z[i]=x[i]+y[i];
  return z;
}

float norma(float *x){
  float norma2=0;
  int i;
  for(i=0; i<3; i++)
    norma2+=x[i]*x[i];
  return sqrt(norma2);
}

float *p_cruz(float *x, float *y){
  float *z=reserva();
  z[0]=x[1]*y[2]-x[2]*y[1];
  z[1]=x[2]*y[0]-x[0]*y[2];
  z[2]=x[0]*y[1]-x[1]*y[0];
  return z;
}


