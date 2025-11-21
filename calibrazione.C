#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLegend.h"
// void Style()
// {
// //     gStyle->SetCanvasPreferGL();
// //     gStyle->SetOptFit(1111);
// //     gStyle->SetOptStat(0);
// //     gStyle->SetStatFont(13);
// //     gStyle->SetTextFont(13);
//     // gStyle->SetTitleFont(13);
//     // gStyle->SetLegendFont(13);
// }


void calibrazione()
{
    TGraphErrors* graph_calibrazione = new TGraphErrors("dati_calibrazione.txt", "%lg%lg%lg%lg");
    TCanvas* canva = new TCanvas("canva", "canva_calibrazione", 0,0, 800, 600);
    TF1 * fit_calibrazione = new TF1("fit_calibrazione", "[0] + [1]*x", 0, 800);
    fit_calibrazione->SetParName(0,"a");
    fit_calibrazione->SetParName(1,"b");
    graph_calibrazione->Fit(fit_calibrazione);
    graph_calibrazione->Draw("APE");
    


    TLegend *legend_calibrazione{new TLegend(0., 1., 0.2, 0.9)};
    // no_limits_no_cl_legend_ampl->SetHeader("Amplitude - Frequency", "C"); // option "C" allows to center the header
    legend_calibrazione->SetNColumns(1);
    // RIGA 1
    legend_calibrazione->AddEntry(graph_calibrazione, "Punti calibrazione", "ep");
    legend_calibrazione->AddEntry(fit_calibrazione, "Fit di calibrazione", "l");
    legend_calibrazione->AddEntry((TObject *)0, (std::string(fit_calibrazione->GetParName(0)) + " = (" + std::to_string(fit_calibrazione->GetParameter(0)) + " ± " +  std::to_string(fit_calibrazione->GetParError(0))+ ") mV").c_str(), "");
    legend_calibrazione->AddEntry((TObject *)0, (std::string(fit_calibrazione->GetParName(1)) + " = (" + std::to_string(fit_calibrazione->GetParameter(1)) + " ± " +  std::to_string(fit_calibrazione->GetParError(1))).c_str(), "");
    legend_calibrazione->Draw();
}