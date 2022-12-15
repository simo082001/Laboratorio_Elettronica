#include <cmath>
#include <vector>

void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

// Funzione caratteristica I-V del diodo
Double_t FitFunction(Double_t *x, Double_t *par) {
  Double_t V_d = x[0];
  Double_t I_0 = par[0];
  Double_t V_t = par[1];
  Double_t val = I_0 * (exp(V_d / V_t) - 1);
  return val;
}

Double_t retta(Double_t *x, Double_t *par) {
  Double_t ics = x[0];
  Double_t emme = par[0];
  Double_t qu = par[1];
  Double_t val = emme * ics + qu;
  return val;
}

void Caratteristica2() {
  // Definisco i grafici
  TGraphErrors *corrente_bassa = new TGraphErrors("Dati_ib_100.txt", "%lg %lg %lg %lg");
  TGraphErrors *corrente_alta = new TGraphErrors("Dati_ib_200.txt", "%lg %lg %lg %lg");

  // cosmetica
  corrente_bassa->SetTitle("Caratteristica con corrente 100 uA");
  corrente_bassa->SetMarkerStyle(7);
  corrente_bassa->SetMarkerColor(kBlue);
  corrente_bassa->SetMarkerSize(6);
  corrente_bassa->GetXaxis()->SetTitle("I_E (mA)");
  corrente_bassa->GetYaxis()->SetTitle("V_E-C (mV)");

  corrente_alta->SetTitle("Caratteristica con corrente 200 uA");
  corrente_alta->SetMarkerStyle(7);
  corrente_alta->SetMarkerColor(kBlue);
  corrente_alta->SetMarkerSize(6);
  corrente_alta->GetXaxis()->SetTitle("I_E (mA)");
  corrente_alta->GetYaxis()->SetTitle("V_E-C (mV)");

  // Assegno le funzioni di fit
  TF1 *f1 = new TF1("ib_100", retta, -22.6, -19.7, 2);
  TF1 *f2 = new TF1("ib_200", retta, -38, -33, 2);

  // Cosmetica
  f1->SetLineWidth(2);
  f2->SetLineWidth(2);
  f1->SetParName(0, "Resistenza di uscita");
  f1->SetParName(1, "Tensione di Early");
  f2->SetParName(0, "Resistenza di uscita");
  f2->SetParName(1, "Tensione di Early");
  

  // Definisco le canvas
  TCanvas *myCanvas1 = new TCanvas("Caratteristica con corrente 100 uA", "canvas 1");
  TCanvas *myCanvas2 = new TCanvas("Caratteristica con corrente 200 uA", "canvas 2");

  corrente_bassa->Fit(f1, "R, C");
  corrente_alta->Fit(f2, "R, C");

  // Disegno i grafici
  gStyle->SetOptFit(111);
  myCanvas1->SetGrid();
  myCanvas1->cd();
  corrente_bassa->Draw("APE, SAME");
  f1->DrawF1(-30, -10, "SAME");
  

  myCanvas2->SetGrid();
  myCanvas2->cd();
  corrente_alta->Draw("APE, SAME");
  f2->DrawF1(-45, -25, "SAME");
}