#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TMath.h"

void fit_diodato()
{
    gStyle->SetCanvasPreferGL();
    TCanvas * canva = new TCanvas ("canva", "Fit canva", 0.,0., 800, 600);
    canva->Divide(2, 1);
    canva->cd(1);

    // TGraphErrors* graph_V_I_Si = new TGraphErrors("V_I_Si.txt", "%lg%lg%lg%lg");
    TGraphErrors* graph_I_V_Si = new TGraphErrors("I_V_Si.txt", "%lg%lg%lg%lg");
    TGraphErrors* graph_Ge = new TGraphErrors("I_V_Ge.txt", "%lg%lg%lg%lg");    

    TF1 * fit_Si = new TF1("fit_Si", "[0]*(TMath::Exp(x/[1]) - 1)", 0, 650);
    // TF1 * fit_Si = new TF1("fit_Si", "[0]*(TMath::Log(x/[1] + 1))", 0.00, 6);
    TF1 * fit_Ge = new TF1("fit_Ge", "[0]*(TMath::Exp(x/[1]) - 1)", 0, 140);
    
    fit_Si->SetParameter(0, 1.484e-6);
    fit_Si->SetParameter(1, 46.05);
    fit_Ge->SetParameter(0, 1.39e-4);
    fit_Ge->SetParameter(1, 22.49);

    fit_Si->SetParName(0,"I0");
    fit_Si->SetParName(1,"eta*VT");
    fit_Ge->SetParName(0,"I0");
    fit_Ge->SetParName(1,"eta*VT");
    

    graph_I_V_Si->Fit(fit_Si, "R");
    graph_Ge->Fit(fit_Ge, "R");
    

    graph_I_V_Si->SetTitle("I-V Silicio");
    graph_Ge->SetTitle("I-V Germanio");

    
    // gPad->SetLogy();
    graph_I_V_Si->Draw("APE");
    canva->cd(2);
    // gPad->SetLogy();
    graph_Ge->Draw("APE");
}