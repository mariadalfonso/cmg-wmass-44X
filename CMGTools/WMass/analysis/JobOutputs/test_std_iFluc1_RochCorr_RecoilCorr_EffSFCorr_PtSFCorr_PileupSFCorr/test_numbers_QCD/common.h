#include <TFile.h>
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLorentzVector.h>

namespace WMass{

  static const double ZMass = 91.188;
  static const int WMassCentral_MeV = 80419;
  static const int WMassStep_MeV = 10;
  static const int WMassNSteps = 0;
  static const int etaMuonNSteps = 1;
  static const float etaMaxMuons[etaMuonNSteps] = { 0.6 };
  static const int nSigOrQCD = 2;
  TString nSigOrQCD_str[nSigOrQCD] = {"Sig","QCD"};
  static const int NFitVar = 3;
  TString FitVar_str[NFitVar] = {"Pt","Mt","MET"};
  static const int PDF_sets = 10042;
  static const int PDF_members = 1;
  static const int NtoysMomCorr = 1;
  
  static const double fit_xmin[3]={30, 60,25};
  static const double fit_xmax[3]={60,120,60};


  // bool isGood_WGenPos_1_Gen(double WGen_m,
                            // int MuGen_charge
                            // ){
    // return (WGen_m>0 && MuGen_charge>0);
  // }

  // bool isGood_WGenPos_2_ZGenMassCut(double WGen_m,
                                    // int MuGen_charge
                                    // ){
    // return isGood_WGenPos_1_Gen(WGen_m,MuGen_charge);
  // }
  
  // bool isGood_WGenPos_3_Mu1GenCut(double WGen_m,
                                    // int MuGen_charge,
                                    // double MuGen_eta,
                                    // double etaMax
                                    // ){
    // return (isGood_WGenPos_2_ZGenMassCut(WGen_m,MuGen_charge)
            // && TMath::Abs(MuGen_eta)<etaMax);
  // }


void plotAndSaveHisto1D(TFile*f1, TString str1, TFile*f2, TString str2, int logx, int logy, int logz, int normalized){

  TH1D*h1=(TH1D*)f1->Get(str1.Data());
  h1->SetLineColor(2);
  TH1D*h2=(TH1D*)f2->Get(str2.Data());
  
  TCanvas *c1 = new TCanvas("c"+str1);
  c1->SetLogx(logx);
  c1->SetLogy(logy);
  c1->SetLogz(logz);
  
  if(normalized){
    h1->DrawNormalized();
    h2->DrawNormalized("same");
  }else{
    h1->Draw();
    h2->Draw("same");    
  }
  
  c1->SaveAs(str1+".png");
  
}

  
}