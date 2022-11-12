#include <cmath>

void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

// Funzione caratteristica I-V del diodo
Double_t FitFunction(Double_t* x, Double_t* par) {
  Double_t V_d = x[0];
  Double_t I_0 = par[0];
  Double_t V_t = par[1];
  Double_t val = I_0 * (exp(V_d / V_t) - 1);
  return val;
}

void caratteristica() {
  // Definisco i grafici
  TGraphErrors* silicio = new TGraphErrors("Dati_Silicio.txt", "%lg %lg %*lg %*lg");
  TGraphErrors* germanio = new TGraphErrors("Dati_Gemanio.txt", "%lg %lg %*lg %*lg");
  TGraphErrors* calibrazione = new TGraphErrors("Calibrazione.txt", "%lg %lg %*lg %*lg");

  // Assegno le funznioni di fit
  TF1* f1 = new TF1("silicio", FitFunction, 350, 760, 2);
  TF1* f2 = new TF1("germanio", FitFunction, 72, 360, 2);

  // Devo settare i parametri iniziali
  f1->SetParameters(5,100);
  f2->SetParameters(4,6);

  // Cosmetica
  silicio->SetTitle("Curva caratteristica silicio");
  silicio->SetMarkerStyle(7);
  silicio->SetMarkerColor(kBlue);
  silicio->SetMarkerSize(4);

  germanio->SetTitle("Curva caratteristica germanio");
  germanio->SetMarkerStyle(7);
  germanio->SetMarkerColor(kRed);
  germanio->SetMarkerSize(4);


  f1->SetLineColor(kRed);
  f1->SetLineStyle(1);
  f1->SetLineWidth(1);
  f1->SetNpx(1000000);

  f2->SetLineColor(kBlue);
  f2->SetLineStyle(1);
  f2->SetLineWidth(1);
  f2->SetNpx(1000000);

  silicio->GetYaxis()->SetTitleOffset(1);
  silicio->GetXaxis()->SetTitleOffset(1.2);
  silicio->GetXaxis()->SetTitle("Tensione (mV)");
  silicio->GetYaxis()->SetTitle("Intensità (mA)");

  germanio->GetYaxis()->SetTitleOffset(1);
  germanio->GetXaxis()->SetTitleOffset(1.2);
  germanio->GetXaxis()->SetTitle("Tensione (mV)");
  germanio->GetYaxis()->SetTitle("Intensità (mA)");

  // Fit dei grafici
  silicio->Fit(f1, "R, C");
  germanio->Fit(f2, "R, C");

  // Volendo c'è da creare le varie Canva
  TCanvas* myCanvas1 = new TCanvas();
  TCanvas* myCanvas2 = new TCanvas();
  TCanvas* myCanvas3 = new TCanvas();

  myCanvas1->SetGrid();
  myCanvas2->SetGrid();
  myCanvas3->SetGrid();

  // Disegno i grafici
  gStyle->SetOptFit(111);
  myCanvas1->cd();
  silicio->Draw("APE, SAME");
  myCanvas2->cd();
  germanio->Draw("APE, SAME");
  f1->Draw("SAME, C");
  f2->Draw("SAME, C");
}