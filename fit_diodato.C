#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TMath.h"

void fit_diodato()
{
    gStyle->SetCanvasPreferGL();
    gStyle->SetGridColor(14);
    gStyle->SetGridStyle(3);
    
    TCanvas *canva = new TCanvas("canva", "Fit canva", 0., 0., 800, 600);
    canva->Divide(2, 1);
    canva->cd(1);

    // TGraphErrors* graph_V_I_Si = new TGraphErrors("V_I_Si.txt", "%lg%lg%lg%lg");
    TGraphErrors *graph_Si = new TGraphErrors("I_V_Si.txt", "%lg%lg%lg%lg");
    TGraphErrors *graph_Ge = new TGraphErrors("I_V_Ge.txt", "%lg%lg%lg%lg");

    TF1 *fit_Si = new TF1("fit_Si", "[0]*(TMath::Exp(x/[1]) - 1)", 0, 650);
    // TF1 * fit_Si = new TF1("fit_Si", "[0]*(TMath::Log(x/[1] + 1))", 0.00, 6);
    TF1 *fit_Ge = new TF1("fit_Ge", "[0]*(TMath::Exp(x/[1]) - 1)", 0, 140);

    fit_Si->SetParameter(0, 1.484e-6);
    fit_Si->SetParameter(1, 46.05);
    fit_Ge->SetParameter(0, 1.39e-4);
    fit_Ge->SetParameter(1, 22.49);

    fit_Si->SetParName(0, "I0");
    fit_Si->SetParName(1, "eta*VT");
    fit_Ge->SetParName(0, "I0");
    fit_Ge->SetParName(1, "eta*VT");

    graph_Si->Fit(fit_Si, "R");
    graph_Ge->Fit(fit_Ge, "R");

    graph_Si->SetTitle("I-V Silicio");
    graph_Si->GetXaxis()->SetTitle("Tensione (mV)");
    graph_Si->GetYaxis()->SetTitle("Corrente (mA)");
    graph_Si->GetXaxis()->SetTitleOffset(1.1);
    graph_Si->GetYaxis()->SetTitleOffset(1.3);

    graph_Ge->SetTitle("I-V Germanio");
    graph_Ge->GetXaxis()->SetTitle("Tensione (mV)");
    graph_Ge->GetYaxis()->SetTitle("Corrente (mA)");
    graph_Ge->GetXaxis()->SetTitleOffset(1.1);
    graph_Ge->GetYaxis()->SetTitleOffset(1.3);

    gPad->SetLogy();
    canva->GetPad(1)->SetGrid();
    graph_Si->Draw("APE");
    
    canva->cd(2);
    gPad->SetLogy();
    canva->GetPad(2)->SetGrid();
    graph_Ge->Draw("APE");
}