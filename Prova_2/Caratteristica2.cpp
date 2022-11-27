#include <cmath>
#include <vector>

void setStyle()
{
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

// Funzione caratteristica I-V del diodo
Double_t FitFunction(Double_t *x, Double_t *par)
{
  Double_t V_d = x[0];
  Double_t I_0 = par[0];
  Double_t V_t = par[1];
  Double_t val = I_0 * (exp(V_d / V_t) - 1);
  return val;
}

void Caratteristica2()
{
  // Definisco i grafici
  TGraphErrors *corrente_bassa = new TGraphErrors("Dati_ib_100.txt", "%lg %lg %lg %lg");
  TGraphErrors *corrente_alta = new TGraphErrors("Dati_ib_200.txt", "%lg %lg %lg %lg");

  // Assegno le funzioni di fit
  TF1 *f1 = new TF1("silicio", FitFunction, 350, 760, 2);
  TF1 *f2 = new TF1("germanio", FitFunction, 72, 320, 2);

  TCanvas *myCanvas1 = new TCanvas("Caratteristica con corrente 100 uA", "canvas 1");
  TCanvas *myCanvas2 = new TCanvas("Caratteristica con corrente 200 uA", "canvas 2");

  myCanvas1->SetGrid();
  myCanvas1->cd();
  corrente_bassa->Draw("APE, SAME");

  myCanvas2->SetGrid();
  myCanvas2->cd();
  corrente_alta->Draw("APE, SAME");
}