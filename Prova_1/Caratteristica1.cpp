#include <cmath>

void setStyle() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

// Funzione caratteristica I-V del diodo
Double_t FitFunction(Double_t* x, Double_t* par) {
  Double_t ics = log(x[0]);
  Double_t emme = par[0];
  Double_t qu = par[1];
  Double_t val = emme * ics + qu;
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
  TGraphErrors* levrini = new TGraphErrors("Dati_Germanio_corretti.txt", "%lg %lg %lg %lg");
  TGraphErrors* barelli = new TGraphErrors("Dati_Silicio_corretti.txt", "%lg %lg %lg %lg");  
  TGraphErrors* silicio = new TGraphErrors("Dati_Silicio.txt", "%lg %lg %lg %lg");
  TGraphErrors* germanio = new TGraphErrors("Dati_Germanio.txt", "%lg %lg %lg %lg");
  TGraphErrors* calibrazione = new TGraphErrors("Calibrazione_corretta.txt", "%lg %lg %lg %lg");
  TGraphErrors* silicioLog = new TGraphErrors("Dati_Silicio.txt", "%lg %lg %lg %lg");
  TGraphErrors* germanioLog = new TGraphErrors("Dati_Germanio.txt", "%lg %lg %lg %lg");

  TMultiGraph* didattica = new TMultiGraph();

  didattica->Add(levrini, "P");
  didattica->Add(barelli, "P");

  // Assegno le funzioni di fit
  TF1* f1 = new TF1("silicio", FitFunction, 0, 3, 2);
  TF1* f2 = new TF1("germanio", FitFunction, 0, 0.5, 2);
  TF1* f3 = new TF1("retta", retta, 0, 750, 2);


  // Devo settare i parametri iniziali
  f1->SetParameters(50, 650);
  f2->SetParameters(50, 250);

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

  levrini->SetTitle("Caratteristica Germanio");
  levrini->SetMarkerStyle(7);
  levrini->SetMarkerSize(6);
  levrini->SetLineColor(kRed);
  levrini->GetXaxis()->SetTitle("V (mV)");
  levrini->GetYaxis()->SetTitle("I (mA)");

  barelli->SetTitle("Caratteristica Silicio");
  barelli->SetMarkerStyle(7);
  barelli->SetMarkerSize(6);
  barelli->SetLineColor(kBlue);
  barelli->GetXaxis()->SetTitle("V (mV)");
  barelli->GetYaxis()->SetTitle("I (mA)");

  didattica->GetYaxis()->SetTitle("Corrente (mA)");
  didattica->GetXaxis()->SetTitle("Tensione (mV)");
  didattica->GetXaxis()->SetTitleOffset(1.2);
  didattica->GetYaxis()->SetTitleOffset(0.8);




  f1->SetLineColor(kRed);
  f1->SetLineStyle(1);
  f1->SetLineWidth(1);
  f1->SetNpx(1000000);

  f2->SetLineColor(kBlue);
  f2->SetLineStyle(1);
  f2->SetLineWidth(1);
  f2->SetNpx(1000000);

  f3->SetLineColor(kViolet);
  f3->SetLineStyle(1);
  f3->SetLineWidth(1);
  f3->SetNpx(1000000);

  silicio->GetYaxis()->SetTitleOffset(1);
  silicio->GetXaxis()->SetTitleOffset(1.2);
  silicio->GetYaxis()->SetTitle("Tensione (mV)");
  silicio->GetXaxis()->SetTitle("Corrente (mA)");

  germanio->GetYaxis()->SetTitleOffset(1);
  germanio->GetXaxis()->SetTitleOffset(1.2);
  germanio->GetYaxis()->SetTitle("Tensione (mV)");
  germanio->GetXaxis()->SetTitle("Corrente (mA)");

  silicioLog->GetYaxis()->SetTitleOffset(1);
  silicioLog->GetXaxis()->SetTitleOffset(1.2);
  silicioLog->GetYaxis()->SetTitle("Tensione (mV)");
  silicioLog->GetXaxis()->SetTitle("Corrente (mA)");

  germanioLog->GetYaxis()->SetTitleOffset(1);
  germanioLog->GetXaxis()->SetTitleOffset(1.2);
  germanioLog->GetYaxis()->SetTitle("Tensione (mV)");
  germanioLog->GetXaxis()->SetTitle("Corrente (mA)");

  calibrazione->GetYaxis()->SetTitleOffset(1);
  calibrazione->GetXaxis()->SetTitleOffset(1.2);
  calibrazione->GetXaxis()->SetTitle("Tensione multimetro (mV)");
  calibrazione->GetYaxis()->SetTitle("Tensione oscilloscopio (mV)");

  // Fit dei grafici
  f1->SetParName(0, "a");
  f2->SetParName(0, "a");
  f1->SetParName(1, "b");
  f2->SetParName(1, "b");
  silicio->Fit(f1, "R, C");
  TFitResultPtr r = germanio->Fit(f2, "S, R");
  r->Print("V");
  //germanio->Fit(f2, "R, C");
  
  //f3->SetParLimits(0, 1, 1.01);
  calibrazione->Fit(f3, "R");
  
  silicioLog->Fit(f1, "R");
  germanioLog->Fit(f2, "R");

  

  // Volendo c'è da creare le varie Canva
  TCanvas* myCanvas1 = new TCanvas("Caratteristica silicio", "canvas 1");
  TCanvas* myCanvas2 = new TCanvas("Caratteristica silicio scala logaritmica", "canvas 2");
  TCanvas* myCanvas3 = new TCanvas("Caratteristica germanio", "canvas 3");
  TCanvas* myCanvas4 = new TCanvas("Caratteristica germanio scala logaritmica", "canvas 4");
  TCanvas* myCanvas5 = new TCanvas("Retta di calibrazione", "canvas 5");
  TCanvas* myCanvas6 = new TCanvas("Multigrafico", "canvas 6");

  std::vector<TCanvas*> Canvas = {myCanvas1, myCanvas2, myCanvas3, myCanvas4, myCanvas5, myCanvas6};
  for (int i = 0; i < 6; i++) {
    Canvas[i]->SetGrid();
  }

  // Disegno i grafici
  gStyle->SetOptFit(111);
  myCanvas1->cd();
  silicio->Draw("APE, SAME");
  f1->DrawF1(0, 8, "SAME");
  myCanvas2->cd();
  gPad->SetLogx();
  silicioLog->Draw("APE, SAME");
  f1->DrawF1(0, 8, "SAME");
  myCanvas3->cd();
  germanio->Draw("APE, SAME");
  f2->DrawF1(0, 8, "SAME");
  myCanvas4->cd();
  gPad->SetLogx();
  germanioLog->Draw("APE, SAME");
  f2->DrawF1(0, 8, "SAME");
  myCanvas5->cd();
  calibrazione->Draw("APE, SAME");
  f3->DrawF1(0, 900, "SAME");
  myCanvas6->cd();
  didattica->Draw("AP");
  myCanvas6->BuildLegend();
}