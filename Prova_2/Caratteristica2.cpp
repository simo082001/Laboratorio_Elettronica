#include <cmath>
#include <vector>

void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void Caratteristica2() {
  // Definisco i grafici
  TGraphErrors* silicio = new TGraphErrors("Dati_Ib100.txt", "%lg %lg %lg %lg");
  TGraphErrors* germanio = new TGraphErrors("Dati_Ib200.txt", "%lg %lg %lg %lg");
  
  // Assegno le funzioni di fit
  TF1* f1 = new TF1("silicio", FitFunction, 350, 760, 2);
  TF1* f2 = new TF1("germanio", FitFunction, 72, 320, 2);


}