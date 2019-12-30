#include "vectores.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// En unidades donde el radio de la tierra es igual a 1
float Q = 2900.0; //q*B_0/m
float c =  47.0;
float m = 938.3;

float *campo(float *r);
float *dv_dt(float *r, float*v);
void runge_kutta(int pasos, float t, float dt, float *r_past, float *v_past, float *r, float *v, FILE *salida);

int main(int argc, char** argv){
  float E = atof(argv[1]);
  float alpha = atof(argv[2])*M_PI/180.0;
  float *r = reserva();
  float *r_past = reserva();
  float *v = reserva();
  float *v_past = reserva();
  
  //condiciones iniciales
  float t=0;
  r[0] = 2;
  r[1] = 0;
  r[2] = 0;
  v[0] = 0;
  v[1] = c*sqrt(1-1/pow((E/(2*m)+1),2))*sin(alpha);
  v[2] = c*sqrt(1-1/pow((E/(2*m)+1),2))*cos(alpha);

  char nombre_salida[20];
  sprintf(nombre_salida, "trayectoria_%f_%f.dat",E,alpha);
  FILE *salida = fopen(nombre_salida, "w");
  fprintf(salida, "%f,%f,%f,%f\n",t,r[0],r[1],r[2]);
  
  copy(r,r_past);
  copy(v,v_past);
  
  int pasos = 100000;
  float dt = 100.0/pasos;
  t+=dt;
  runge_kutta(pasos,t,dt,r_past,v_past,r,v,salida);
  fclose(salida);

  return 0;
}

//campo magbnetico efectivo
float *campo(float *r){
  float *B = reserva();
  B[0]=-Q/pow(norma(r),5)*3*r[0]*r[2];
  B[1]=-Q/pow(norma(r),5)*3*r[1]*r[2];
  B[2]=-Q/pow(norma(r),5)*(2*pow(r[2],2)-pow(r[1],2)-pow(r[0],2));
  return B;
}

float *dv_dt(float *r, float*v){
  float gamma_inv = sqrt(1-pow(norma(v)/c,2));
  float *m = p_escalar(gamma_inv, p_cruz(v, campo(r)));
  return m;
}

void runge_kutta(int pasos, float t, float dt, float *r_past, float *v_past, float *r, float *v, FILE *salida){
  int i;
  for(i=1; i<pasos; i++){
    float *k1 = dv_dt(r_past,v_past);
    float *v1 = suma_vec(p_escalar(dt/2.0,k1),v_past);
    float *r1 = suma_vec(p_escalar(dt/2.0,v),r_past);
    float *k2 = dv_dt(r1,v1);
    float *v2 = suma_vec(p_escalar(dt/2.0,k2),v_past);
    float *r2 = suma_vec(p_escalar(dt/2.0,v1),r_past);
    float *k3 = dv_dt(r2,v2);
    float *v3 = suma_vec(p_escalar(dt,k3),v_past);
    float *r3 = suma_vec(p_escalar(dt,v2),r_past);
    float *k4 = dv_dt(r3,v3);

    float *k_f = p_escalar(1/6.0, suma_vec(p_escalar(2.0,suma_vec(k2,k3)),suma_vec(k1,k4)));
    float *v_f = p_escalar(1/6.0, suma_vec(p_escalar(2.0,suma_vec(v1,v2)),suma_vec(v,v3)));

    t+=dt;
    r = suma_vec(p_escalar(dt, v_f), r_past);
    v = suma_vec(p_escalar(dt, k_f), v_past);
    copy(r, r_past);
    copy(v, v_past);

    fprintf(salida,"%f,%f,%f,%f\n",t,r[0],r[1],r[2]);
  }
}
