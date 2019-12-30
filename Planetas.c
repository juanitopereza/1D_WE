#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define rows 10
#define cols 10000
#define G 39.4784176043574344753379 // Constante gravitacional en UA^3*(M_sol)^-1*(yr)^-2

void CondIni(double* masas, double* posX, double* posY, double* posZ, double* velX, double* velY, double* velZ, double matriz[10][8]);
void imprimeM(double data[10][8]);
void imprimeV(double* data);
void TiempoUno(double* masas, double* posX, double* posY, double* posZ, double* velX, double* velY, double* velZ, double dt);
double Accel(double* masas, double* posX, double* posY, double* posZ, int t, int p, char comp[]);
void Evoluciona(double* masas, double* posX, double* posY, double* posZ, double* velX, double* velY, double* velZ, double dt, int t);

int main(void){
	FILE *datos;
	datos=fopen("coordinates.csv","r");
	int len=300;
	char ap[len];
	char *ep;
	const char *delimiter;
	delimiter= ",";
	double matrix[10][8];
	int i=0, j=0;
  while(fgets(ap,len,datos)){
		j=0;
		//printf("LINE IS:%s", line_buffer );
		ep = strtok(ap,delimiter);
    while(ep != NULL){
    	if(j!=0){
      	matrix[i][j-1] = atof(ep);
        //printf("ITEM IN LINE: %s",split_buffer);
        ep= strtok(NULL,delimiter);
      }
			j+=1;
    }
    i+=1;
  }

  //imprimeM(matrix);
	static double dt = 0.001;
	double *x = (double *)malloc(rows*cols*sizeof(double));
	double *y = (double *)malloc(rows*cols*sizeof(double));
	double *z = (double *)malloc(rows*cols*sizeof(double));
	double *vx = (double *)malloc(rows*cols*sizeof(double));
	double *vy = (double *)malloc(rows*cols*sizeof(double));
	double *vz = (double *)malloc(rows*cols*sizeof(double));
	double *m = (double *)malloc(rows*sizeof(double));
	double *times = (double *)malloc(cols*sizeof(double));
	CondIni(m,x,y,z,vx,vy,vz,matrix);
	TiempoUno(m,x,y,z,vx,vy,vz,dt);
	times[0] = 0.0;
	times[1] = dt;
	for (int i = 2; i < cols; i++) {
		times[i] = times[i-1] + dt;
		Evoluciona(m,x,y,z,vx,vy,vz,dt,i);
	}
	FILE *fout;
	fout = fopen("Pos_Planetas.csv", "w");
	for (int j = 0; j < cols; j++) {
		for (int i = 0; i < rows; i++) {
			if (i==0) {
				fprintf(fout,"%lf,%lf,%lf,%lf,",times[j], x[i*cols+j], y[i*cols+j], z[i*cols+j]);
			} else if (i==9) {
				fprintf(fout,"%lf,%lf,%lf\n", x[i*cols+j], y[i*cols+j], z[i*cols+j]);
			} else {
				fprintf(fout,"%lf,%lf,%lf,", x[i*cols+j], y[i*cols+j], z[i*cols+j]);
			}
		}
	}
	//imprimeV(vx);
}
void CondIni(double* masas, double* posX, double* posY, double* posZ, double* velX, double* velY, double* velZ, double matriz[10][8]){

    for (int i=0;i<rows;i++){
			  //guarda masas en masas solares.
        masas[i] = matriz[i][1]*5.029081E-31;
				//guarda posiciones en pc.
				posX[i*cols+0] = matriz[i][2];
				posY[i*cols+0] = matriz[i][3];
				posZ[i*cols+0] = matriz[i][4];
				velX[i*cols+0] = matriz[i][5]*0.2108;
				velY[i*cols+0] = matriz[i][6]*0.2108;
				velZ[i*cols+0] = matriz[i][7]*0.2108;
    }
}
void TiempoUno(double* masas, double* posX, double* posY, double* posZ, double* velX, double* velY, double* velZ, double dt){
	for (int i = 0; i < rows; i++) {
		posX[i*cols+1] = posX[i*cols+0]+dt*velX[i*cols+0];
		posY[i*cols+1] = posY[i*cols+0]+dt*velY[i*cols+0];
		posZ[i*cols+1] = posZ[i*cols+0]+dt*velZ[i*cols+0];
		//printf("ax[%d] es : %lf\n",i, Accel(masas, posX, posY, posZ, 0, i, "x"));
		velX[i*cols+1] = velX[i*cols+0]+dt*Accel(masas, posX, posY, posZ, 0, i, "x");
		velY[i*cols+1] = velY[i*cols+0]+dt*Accel(masas, posX, posY, posZ, 0, i, "y");
		velZ[i*cols+1] = velZ[i*cols+0]+dt*Accel(masas, posX, posY, posZ, 0, i, "z");
	}
}
void Evoluciona(double* masas, double* posX, double* posY, double* posZ, double* velX, double* velY, double* velZ, double dt, int t){
	for (int i = 0; i < rows; i++) {
		posX[i*cols+t] = posX[i*cols+t-2]+2*dt*velX[i*cols+t-1];
		posY[i*cols+t] = posY[i*cols+t-2]+2*dt*velY[i*cols+t-1];
		posZ[i*cols+t] = posZ[i*cols+t-2]+2*dt*velZ[i*cols+t-1];

		velX[i*cols+t] = velX[i*cols+t-2]+2*dt*Accel(masas, posX, posY, posZ, t-1, i, "x");
		//printf("ax[%d] es : %lf\n",i, Accel(masas, posX, posY, posZ, 0, i, "x"));
		velY[i*cols+t] = velY[i*cols+t-2]+2*dt*Accel(masas, posX, posY, posZ, t-1, i, "y");
		//printf("ay[%d] es : %lf\n",i, Accel(masas, posX, posY, posZ, 0, i, "y"));
		velZ[i*cols+t] = velZ[i*cols+t-2]+2*dt*Accel(masas, posX, posY, posZ, t-1, i, "z");
		//printf("az[%d] es : %lf\n",i, Accel(masas, posX, posY, posZ, 0, i, "z"));
	}
}
double Distancia(double* posX,  double* posY,  double* posZ, int t, int p1, int p2){
	double d=0;
	d = sqrt(pow(posX[p1*cols+t]-posX[p2*cols+t],2) + pow(posY[p1*cols+t]-posY[p2*cols+t],2) + pow(posZ[p1*cols+t]-posZ[p2*cols+t],2));
  return d;
}
double Accel(double* masas, double* posX, double* posY, double* posZ, int t, int p, char comp[]){
	double a = 0;
	double r3 = 0;
	for (int i = 0; i < rows; i++) {
		if(i!=p){
			if (strcmp(comp,"x") == 0) {
				r3 = pow(Distancia(posX,posY,posZ,t,p,i),3);
				a += G*masas[i]*(posX[i*cols+t]-posX[p*cols+t])/r3;
			}
			if (strcmp(comp,"y") == 0) {
				r3 = pow(Distancia(posX,posY,posZ,t,p,i),3);
				a += G*masas[i]*(posY[i*cols+t]-posY[p*cols+t])/r3;
			}
			if (strcmp(comp,"z") == 0) {
				r3 = pow(Distancia(posX,posY,posZ,t,p,i),3);
				a += G*masas[i]*(posZ[i*cols+t]-posZ[p*cols+t])/r3;
			}
		}
	}
	return a;
}
void imprimeM(double data[10][8]){
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 8; j++) {
      printf("Datos[%d][%d] es: %f\n",i,j,data[i][j]);
    }

  }
}
void imprimeV(double* data){
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 2; j++) {
      printf("vx[%d][%d] es: %f\n",i,j,data[i*cols+j]);
    }

  }
}
