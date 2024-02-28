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

#define NAMEFILE "matita2h"

#define MAXARRXY 100

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

 	double funct(double *xcoord, double *par){
	return xcoord[0]*par[0];
	}

void chi2(int &npar, double *deriv, double &f, double *par, int flag){
    f = 0;
	for (int i=0;i<ndat;i++) {
	   f += pow((y[i]-funct(&x[i],par)),2)/(pow(ey[i],2)+pow(ex[i]*par[0],2));
	}
}

#define npar 1

int Linfit0(){
	//gROOT->Reset();
	ReadDati(ndat, x, y, ex, ey);
	TCanvas * tela = new TCanvas("c1","Grafico 1",200,10,700,500); ; // crea (e apre) la finestra grafica
	TGraphErrors * gr = new TGraphErrors(ndat,x,y,ex,ey); // crea il grafico
	// Minuit
	TMinuit minuit(npar); // inizializzo con il numero di parametri
	minuit.SetFCN(chi2); // dice qual’e la funzione che calcola il chi2
	minuit.SetErrorDef(1.); // definisce Delta(chi2)=1 per calcolare l’errore
	double par[npar] ={0.00};
	double step[npar]={0.001};
	double min[npar] ={0.00};
	double max[npar] ={0.00};
	string cpar[npar]={ "coeff"}; // nomi delle variabili;
	//for (int i=0;i<npar;i++){
		minuit.DefineParameter(0,cpar[0].c_str(),par[0],step[0],min[0],max[0]);
		// assegna nome, val in, step, min, max per il parametro 1
	//}
	minuit.Migrad(); // invoca il metodo di minimizzazione Migrad
	double outpar[npar],err[npar];
	//for (int i=0;i<npar;i++){
		minuit.GetParameter(0,outpar[0],err[0]); // restituisce il valore dei parametri
	//}
	TF1 *func = new TF1("funcplot",funct,0,600,npar); // crea il grafico di funzione a npar parametri
	func->SetParameters(outpar); // assegna i valori fittati ai due parametri della funzione
	gr->SetTitle(TITLE);
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
	gr->GetXaxis()->SetTitle("l (mm)");
	gr->GetYaxis()->SetTitle(" R (#Omega)");
	gr->SetTitle("Grafico");
	gr->Draw("AP"); // disegna il grafico
	TCanvas *canvas2 = new TCanvas("c2", "Grafico 2", 200, 10, 700, 500);
	gr->Draw("ALP");

	func->Draw("SAME"); // disegna la funzione sovrapposta
	//myapp.Run(true); // runna l’interfaccia grafica dando all’utente la possibilita’
	// di intervenire
	//tela.Close(); // chiude la finestra
	return 0;
}
