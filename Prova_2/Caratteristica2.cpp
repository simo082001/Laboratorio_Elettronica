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
  TGraphErrors *corrente_bassa1 = new TGraphErrors("Datiscambiati100.txt", "%lg %lg %lg %lg");

  TGraphErrors *corrente_alta = new TGraphErrors("Dati_ib_200.txt", "%lg %lg %lg %lg");
  TGraphErrors *corrente_alta1 = new TGraphErrors("Datiscambiati200.txt", "%lg %lg %lg %lg");

  TMultiGraph *multigrafico = new TMultiGraph();
  multigrafico->Add(corrente_bassa1, "P");
  multigrafico->Add(corrente_alta1, "P");

  // cosmetica
  corrente_bassa->SetTitle("Caratteristica con corrente 100 uA");
  corrente_bassa->SetMarkerStyle(7);
  corrente_bassa->SetMarkerColor(kBlue);
  corrente_bassa->SetMarkerSize(6);
  corrente_bassa->GetXaxis()->SetTitle("Corrente di collettore |Ic| (mA)");
  corrente_bassa->GetYaxis()->SetTitle("Tensione tra collettore ed emettitore |Vce| (mV)");

  corrente_bassa1->SetTitle("Caratteristica con corrente 100 uA");
  corrente_bassa1->SetMarkerStyle(7);
  // corrente_bassa1->SetMarkerColor(kBlue);
  corrente_bassa1->SetMarkerSize(6);
  corrente_bassa1->SetLineColor(kBlue);
  corrente_bassa1->GetXaxis()->SetTitle("Tensione tra collettore ed emettitore |Vce| (mV)");
  corrente_bassa1->GetYaxis()->SetTitle("Corrente di collettore |Ic| (mA)");


  corrente_alta->SetTitle("Caratteristica con corrente 200 uA");
  corrente_alta->SetMarkerStyle(7);
  corrente_alta->SetMarkerColor(kGreen);
  corrente_alta->SetMarkerSize(6);
  corrente_alta->GetXaxis()->SetTitle("Corrente di collettore |Ic| (mA)");
  corrente_alta->GetYaxis()->SetTitle("Tensione tra collettore ed emettitore |Vce| (mV)");

  corrente_alta1->SetTitle("Caratteristica con corrente 200 uA");
  corrente_alta1->SetMarkerStyle(7);
  // corrente_alta1->SetMarkerColor(kRed);
  corrente_alta1->SetMarkerSize(8);
  corrente_alta1->SetLineColor(kRed);
  corrente_alta1->GetXaxis()->SetTitle("Tensione tra collettore ed emettitore |Vce| (mV)");
  corrente_alta1->GetYaxis()->SetTitle("Corrente di collettore |Ic| (mA)");


  multigrafico->GetYaxis()->SetTitle("Corrente di collettore |Ic| (mA)");
  multigrafico->GetXaxis()->SetTitle("Tensione tra collettore ed emettitore |Vce| (mV)");
  multigrafico->GetXaxis()->SetTitleOffset(1.2);


  // Assegno le funzioni di fit
  TF1 *f1 = new TF1("ib_100", retta, 19.7, 22.6, 2);
  TF1 *f2 = new TF1("ib_200", retta, 33, 38, 2);

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
  TCanvas *myCanvas3 = new TCanvas("Multigrafico caratteristiche", "canvas 3");


  corrente_bassa->Fit(f1, "R, C");
  corrente_alta->Fit(f2, "R, C");

  // Disegno i grafici
  gStyle->SetOptFit(111);
  myCanvas1->SetGrid();
  myCanvas1->cd();
  corrente_bassa->Draw("APE, SAME");
  f1->DrawF1(10, 30, "SAME");  

  myCanvas2->SetGrid();
  myCanvas2->cd();
  corrente_alta->Draw("APE, SAME");
  f2->DrawF1(25, 45, "SAME");

  myCanvas3->SetGrid();
  myCanvas3->cd();
  multigrafico->Draw("AP");
  myCanvas3->BuildLegend();
}