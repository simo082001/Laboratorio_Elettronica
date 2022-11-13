#include <cmath>
#include <vector>

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
  TGraphErrors* silicioLog = new TGraphErrors("Dati_Silicio.txt", "%lg %lg %*lg %*lg");
  TGraphErrors* germanioLog = new TGraphErrors("Dati_Gemanio.txt", "%lg %lg %*lg %*lg");

  // Assegno le funznioni di fit
  TF1* f1 = new TF1("silicio", FitFunction, 350, 760, 2);
  TF1* f2 = new TF1("germanio", FitFunction, 72, 360, 2);

  // Devo settare i parametri iniziali
  f1->SetParameters(5, 100);
  f2->SetParameters(4, 6);

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
  TCanvas* myCanvas1 = new TCanvas("Caratteristica silicio");
  TCanvas* myCanvas2 = new TCanvas("Caratteristica silicio scala logaritmica");
  TCanvas* myCanvas3 = new TCanvas("Caratteristica germanio");
  TCanvas* myCanvas4 = new TCanvas("Caratteristica germanio scala logaritmica");
  TCanvas* myCanvas5 = new TCanvas("Retta di calibrazione");

  std::vector<TCanvas*> Canvas = {myCanvas1, myCanvas2, myCanvas3, myCanvas4, myCanvas5};
  for (int i = 0; i < 0; i++) {
    Canvas[i]->SetGrid();
  }

  // Disegno i grafici
  gStyle->SetOptFit(111);
  myCanvas1->cd();
  silicio->Draw("APE, SAME");
  myCanvas2->cd();
  gPad->SetLogy();
  silicioLog->Draw("APE, SAME");
  myCanvas3->cd();
  germanio->Draw("APE, SAME");
  myCanvas4->cd();
  germanioLog->Draw("APE, SAME");
  myCanvas5->cd();
  calibrazione->Draw("APE, SAME");
  f1->Draw("SAME, C");
  f2->Draw("SAME, C");
}