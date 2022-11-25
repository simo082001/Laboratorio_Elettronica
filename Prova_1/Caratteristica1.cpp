#include<cmath>

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

// Scriviamo anche la retta. Sono molto simpatico XD
Double_t retta(Double_t* x, Double_t* par) {
  Double_t ics = x[0];
  Double_t emme = par[0];
  Double_t qu = par[1];
  Double_t val = emme * ics + qu;
  return val;
}

void Caratteristica1() {
  // Definisco i grafici
  TGraphErrors* silicio = new TGraphErrors("Dati_Silicio.txt", "%lg %lg %lg %lg");
  TGraphErrors* germanio = new TGraphErrors("Dati_Germanio.txt", "%lg %lg %lg %lg");
  TGraphErrors* calibrazione = new TGraphErrors("Calibrazione_corretta.txt", "%lg %lg %lg %lg"); 
  // bisogna modificare con gli errori in qudratura per l'oscilloscopio
  TGraphErrors* silicioLog = new TGraphErrors("Dati_Silicio.txt", "%lg %lg %lg %lg");
  TGraphErrors* germanioLog = new TGraphErrors("Dati_Germanio.txt", "%lg %lg %lg %lg");

  // Assegno le funzioni di fit
  TF1* f1 = new TF1("silicio", FitFunction, 350, 760, 2);
  TF1* f2 = new TF1("germanio", FitFunction, 72, 320, 2);
  TF1* f3 = new TF1("retta", retta, 0, 800, 2);

  // Devo settare i parametri iniziali
  f1->SetParameters(5, 100);
  f2->SetParameters(5, 100);

  // Cosmetica
  silicio->SetTitle("Curva caratteristica silicio");
  silicio->SetMarkerStyle(7);
  silicio->SetMarkerColor(kBlue);
  silicio->SetMarkerSize(4);

  silicioLog->SetTitle("Curva caratteristica silicio - scala semilogaritmica");
  silicioLog->SetMarkerStyle(7);
  silicioLog->SetMarkerColor(kBlue);
  silicioLog->SetMarkerSize(4);

  germanio->SetTitle("Curva caratteristica germanio");
  germanio->SetMarkerStyle(7);
  germanio->SetMarkerColor(kRed);
  germanio->SetMarkerSize(4);

  germanioLog->SetTitle("Curva caratteristica germanio - scala semilogaritmica");
  germanioLog->SetMarkerStyle(7);
  germanioLog->SetMarkerColor(kRed);
  germanioLog->SetMarkerSize(4);

  calibrazione->SetTitle("Retta di calibrazione");
  calibrazione->SetMarkerStyle(7);
  calibrazione->SetMarkerColor(kBlue);
  calibrazione->SetMarkerSize(4);

  f1->SetLineColor(kRed);
  f1->SetLineStyle(1);
  f1->SetLineWidth(1);
  f1->SetNpx(1000000);

  f2->SetLineColor(kBlue);
  f2->SetLineStyle(1);
  f2->SetLineWidth(1);
  f2->SetNpx(1000000);

  f3->SetLineColor(kRed);
  f3->SetLineStyle(1);
  f3->SetLineWidth(1);
  f3->SetNpx(1000000);

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
  calibrazione->Fit(f3, "R, C");

  // Volendo c'è da creare le varie Canva
  TCanvas* myCanvas1 = new TCanvas("Caratteristica silicio", "canvas 1");
  TCanvas* myCanvas2 = new TCanvas("Caratteristica silicio scala logaritmica", "canvas 2");
  TCanvas* myCanvas3 = new TCanvas("Caratteristica germanio", "canvas 3");
  TCanvas* myCanvas4 = new TCanvas("Caratteristica germanio scala logaritmica", "canvas 4");
  TCanvas* myCanvas5 = new TCanvas("Retta di calibrazione", "canvas 5");

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
  gPad->SetLogy();
  germanioLog->Draw("APE, SAME");
  myCanvas5->cd();
  calibrazione->Draw("APE, SAME");
}