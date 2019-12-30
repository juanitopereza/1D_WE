#include<stdlib.h>
#include<stdio.h>
#include<math.h>

float T = 40;
float rho = 10;
float L = 100;
float tiempo = 200;
int puntos = 101;

void cond_ini(float *u, int puntos);
void escribe(float *u, char *filename, int puntos); 
float *copia(float *A, int puntos);

int main(){

  int i;
  float c = sqrt(T/rho);
  float t = 0;
  float dx = L/(puntos-1);
  float dt = 0.5*dx/c; 
  float c_prima = dx/dt; //courant cond
  char filename[100]="datos_cuerda.dat";

  float *u = malloc(puntos*sizeof(float));
  float *u_1 = malloc(puntos*sizeof(float));
  float *u_2 = malloc(puntos*sizeof(float));
  
  cond_ini(u,puntos);
  escribe(u,filename,puntos);

  u_1 = copia(u, puntos);
  t += dt;
  for(i=1;i<puntos-1;i++){
    u[i] = u_1[i] + ((c*c)/(c_prima*c_prima))*(u_1[i+1] + u_1[i-1] - 2*u_1[i]);  
  }
  escribe(u,filename,puntos);

  u_2 = copia(u_1, puntos);
  u_1 = copia(u, puntos);

  while(t<tiempo){
    t += dt;
    for(i=1;i<puntos-1;i++){
      u[i] = 2*u_1[i] - u_2[i] + ((c*c)/(c_prima*c_prima))*(u_1[i+1] + u_1[i-1] - 2*u_1[i]);
    }
    escribe(u,filename,puntos);
    u_2 = copia(u_1, puntos);
    u_1 = copia(u, puntos);
  }
  return 0;
}

void escribe(float *u, char *filename, int puntos){

  FILE *in;
  int i;
  in = fopen(filename,"a");
  for(i=0;i<puntos-1;i++){
    fprintf(in,"%f ", u[i]);
}
  fprintf(in,"%f\n", u[-1]);
  fclose(in);
}

float *copia(float *A, int puntos){
  int i; 
  float *B = malloc(puntos*sizeof(float));
  for (i=0; i<puntos; i++){
    B[i]=A[i];
}
  return B;
}

void cond_ini(float *u, int puntos){

  int i;
  u[0] = 0;
  u[puntos-1] = 0;
  for(i=1; i<81; i++){
    u[i] = 0.0125*i;
  }
  for(i=81; i<puntos-1; i++){
    u[i] = 5-0.05*i;
  }
}
