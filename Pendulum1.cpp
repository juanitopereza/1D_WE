#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

const double wO=1., gama=0.2;
const double h=0.1, delta=1.0;
const double F=1.4, w=0.2;
const int N=1000;
double g(double thetaO, double omegaO, double t);
double f(double thetaO, double omegaO, double t,double force);

int main(void){
  ofstream outfile;
  outfile.open("Datos2.dat");
  double omega=1;
  double theta=0.01;
  for(int i=0;i<N;i++){
    outfile<<i*h<<'\t'<<theta<<'\t'<<omega<<endl;
    omega=omega+h*f(theta,omega,i*h,F);
    theta=theta+h*g(theta,omega,i*h);
  }
  outfile.close();
  //Diagrama de Bifurcacion
  outfile.open("Bifurcacion.dat");

  double fStart=1.20;
  double fEnd=1.459;
  double paso=(fEnd-fStart)/300;
  double tIni=0;
  double PI = 3.14159265358979323846;
  double tFinal=9*PI;
  double pasoT=(tFinal-tIni)/600;
  omega=1;
  theta=0;
  //El for externo mueve la fuerza para que las fuerzas estene en el rango en el cual se muestran en la grafica del libro
  for(double i=0;i<300;i++){
    //Se mueve este for en el timepo para que se mueva 600 veces el angulo con respecto al timpo y se imprima el angulo en un tiempo multiplo de 3pi
    //No me grafica bien, revisa esta parte porfa cambie h por el paso, no se si este correcto
    for(double j=0;j<601;j++){
    omega=omega+pasoT*f(theta,omega,j*pasoT,fStart+i*paso);
    theta=theta+pasoT*g(theta,omega,j*pasoT);
  }
    outfile<<theta<<' '<<fStart+i*paso<<endl;
  }
  outfile.close();
  return 0;
}
 double g(double thetaO, double omegaO,double t ){
   return omegaO;
 }
 double f(double thetaO, double omegaO,double t, double Force){
   return -wO*wO*sin(thetaO)-gama*omegaO+F*sin(w*t+delta);
 }
