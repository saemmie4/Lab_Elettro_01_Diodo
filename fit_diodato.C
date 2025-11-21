#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLegend.h"

void fit_diodato()
{
    TGraphErrors* graph_Si = new TGraphErrors("I_V_Si.txt", "%lg%lg%lg%lg");
    TGraphErrors* graph_Ge = new TGraphErrors("I_V_Ge.txt", "%lg%lg%lg%lg");

    // TF1 * fit_Si = new TF1("fit_Si", "[0] + [1]*x", 0, 800);
    // TF1 * fit_Ge = new TF1("fit_Ge", "[0] + [1]*x", 0, 800);
    

    TF1 * fit_Si = new TF1("fit_Si", "[0]*(TMath::Exp(x/[1]) - 1)", 0, 800);
    TF1 * fit_Ge = new TF1("fit_Ge", "[0]*(TMath::Exp(x/[1]) - 1)", 0, 800);
    

    fit_Si->SetParName(0,"a");
    fit_Si->SetParName(1,"b");
    fit_Ge->SetParName(0,"a");
    fit_Ge->SetParName(1,"b");
    

    graph_Si->Fit(fit_Si);
    graph_Ge->Fit(fit_Ge);
    

    graph_Si->SetTitle("I-V Silicio");
    graph_Ge->SetTitle("I-V Germanio");

    
    TCanvas * canva = new TCanvas ("canva", "Fit canva", 0.,0., 800, 600);
    canva->Divide(2, 1);
    canva->cd(1);
    // gPad->SetLogy();
    graph_Si->Draw("APE");
    canva->cd(2);
    // gPad->SetLogy();
    graph_Ge->Draw("APE");
}