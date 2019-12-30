#include<stdlib.h>
#include<stdio.h>
#include<math.h>

float L = 5;
float l = 2;
float d = 1;
float h = 0.02;
float V_0 = 100;

void cond_ini(float *U, float *E_x, float *E_y, int puntos, int l_n, int d_c, float V_0);

float *copia(float *A, int puntos);

void escribe(float *u, char *filename, int puntos);

int main(){
  
  int puntos = L/h;
  if(puntos%2==0){
    puntos += 1;
  }
  int l_n = l/h;
  if(l_n%2==0){
    l_n += 1;
  }
  int d_c = d/(2*h);
  if(dc%2==0){
    d_c += 1;
  }
  
  float N = 2*pow(L/h,2);
  
  char filename1[100] = "potencial.dat";
  char filename2[100] = "campo.dat";
  
  float *U = malloc(puntos*puntos*sizeof(float));
  float *U_temp = malloc(puntos*puntos*sizeof(float));
  float *E_x = malloc(puntos*puntos*sizeof(float));
  float *E_y = malloc(puntos*puntos*sizeof(float));
  
  cond_ini(U,E_x,E_y,puntos,l_n,d_c,V_0);

  int t = 0;
  
  U_temp = copia(U,puntos);

  while(t<N){
    t += 1;
    
    for(i=1; i<puntos-1; i++){
      for(j=1; j<puntos-1;j++){
	U_temp = copia(U,puntos);
	U[i*puntos + j] = (1/4)*(U[(i+1)*puntos + j] + U[(i-1)*puntos + j] + U[i*puntos + (j+1)] + U[i*puntos + (j-1)]);
	
	if((j==(puntos/2) + d_c) && (i==(puntos/2)-l_n/2) && (i==(puntos/2)+l_n/2)){
	  U[i*puntos + j] = V_0/2;
	}
	if((j==(puntos/2) - d_c) && (i==(puntos/2)-l_n/2) && (i==(puntos/2)+l_n/2)){
	  U[i*puntos + j] = -V_0/2;
	}
      }
    }
  }
  
  escribe(U,filename1,puntos);

  return 0;
}

void cond_ini(float *U, float *E_x, float *E_y, int puntos, int l_n, int d_c, float V_0){

  int i;
  int j;
  for(i=0; i<puntos; i++){
    for(j=0; j<puntos; j++){
      U[i*puntos + j] = 0;
    }
  }
  for(i=1; i<puntos-1; i++){
    for(j=1; j<puntos-1; j++){
      
      U[i*puntos + j] = 0.05;
      
      if((j==(puntos/2) + d_c) && (i==(puntos/2)-l_n/2) && (i==(puntos/2)+l_n/2)){
	U[i*puntos + j] = V_0/2;
      }
      if((j==(puntos/2) - d_c) && (i==(puntos/2)-l_n/2) && (i==(puntos/2)+l_n/2)){
	U[i*puntos + j] = -V_0/2;
      }
    }
  }
  
  for(i=0; i<puntos; i++){
    for(j=0; j<puntos; j++){
      E_x[i*puntos + j] = 0;
      E_y[i*puntos + j] = 0;
    }
  }
}

float *copia(float *A, int puntos){
  int i; 
  float *B = malloc(puntos*sizeof(float));
  for (i=0; i<puntos; i++){
    B[i]=A[i];
}
  return B;
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
