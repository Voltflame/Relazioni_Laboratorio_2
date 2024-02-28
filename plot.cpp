#include <TCanvas.h>
#include <TApplication.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <cmath>
#include <TMinuit.h>
#include <string>
#include <fstream>
#include <TAxis.h>

using namespace std;

//TApplication myapp("app",NULL,NULL); // crea l’interfaccia grafica
// Per utilizzare Minuit e’ necessario che le coordinate dei punti
// siano globali

#define TITLE "Prova Grafico; asse X ; asse Y"

#define NAMEFILE "Scarica50.txt"

#define MAXARRXY 150

double x[MAXARRXY];
double y[MAXARRXY];
double ex[MAXARRXY];
double ey[MAXARRXY];


int ndat;
void ReadDati(int &n, double *xx, double *yy, double *exx, double *eyy)
{
	ifstream inp;
	double v1,v2,v3,v4;
	ndat=0;
    inp.open(NAMEFILE);
	while (inp>>v1>>v2>>v3>>v4) { 
      	 *(yy+n)=v1; printf("y=%f ",v1);  
      	 *(eyy+n)=v2; printf("ey=%f ",v2); 	
	 *(xx+n)=v3; printf("x=%f ",v3); 	
	 *(exx+n)=v4; printf("ex=%f ",v4); 	
	  n++;
	  printf("n=%d \n",n); 
    	}
    	cout<<inp.eof()<<endl; 	
	inp.close();
}
int plot(){
//gROOT->Reset();
	ReadDati(ndat, x, y, ex, ey);
	TCanvas * tela = new TCanvas("c1","Grafico 1",200,10,700,500); ; // crea (e apre) la 		finestra grafica
	TGraphErrors * gr = new TGraphErrors(ndat,x,y,ex,ey);
	gr->SetMarkerColor(4);
    	gr->SetMarkerStyle(21);
	gr->GetXaxis()->SetTitle("(#frac{1}{T_{0}} - #frac{1}{T}) K^{-1})");
	gr->GetYaxis()->SetTitle("#frac{R_{n}}{R_{n}(T_{0})} ");
	gr->SetTitle("Grafico 4");
	gr->Draw("AP"); // disegna il grafico
	return 0;
	}
