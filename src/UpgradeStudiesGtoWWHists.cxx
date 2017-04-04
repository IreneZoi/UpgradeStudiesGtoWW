#include "UHH2/UpgradeStudiesGtoWW/include/UpgradeStudiesGtoWWHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/JetHists.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

UpgradeStudiesGtoWWHists::UpgradeStudiesGtoWWHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  //******************* book all histograms here *****************************

  //ratios (Reco -Gen)/Gen
  book<TH1F>("Mass_Ratio", "(RecoJetMass-GenJetMass)/GenJetMass", 100, -2, 8); //irene
  //  book<TH1F>("Tau_Ratio", "(RecoTau21-GenTau21)/GenTau21", 100,-100000, 100000); //irene                                                                                                                
  //  book<TH1F>("Tau_Ratio", "(RecoTau21-GenTau21)/RecoTau21", 100,-1, 2); //irene 
  book<TH1F>("Tau21_Gen", "#tau_2/#tau_1", 50,-15e-17,15e-17); //irene                                                                                                                     
  //book<TH1F>("Tau21_Reco", "#tau_2/#tau_1", 100,0,1); //irene 
  //  book<TH1F>("CHF_Gen", "CHF", 100,0,1); //irene  
  //book<TH1F>("CHF_Gen_1", "CHF_1", 100,1e-314,1e-316); //irene 
  //  book<TH1F>("CHF_Ratio", "(RecoCHF-GenCHF)/GenCHF", 100,-1,1); //irene  
  book<TH1F>("SoftDropMass_Gen", "GenJetSoftDropMass [GeV/c^2]", 100,0,300);
  book<TH1F>("SoftDropMass_ratio", "(RecoSDMass-GenSDMass)/GenSDMass", 100,-1,1);

  // jets
  book<TH1F>("N_jets", "N_{jets}", 20, 0, 20);  
  book<TH1F>("eta_jet1", "#eta^{jet 1}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet2", "#eta^{jet 2}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet3", "#eta^{jet 3}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet4", "#eta^{jet 4}", 40, -2.5, 2.5);

  // leptons
  book<TH1F>("N_mu", "N^{#mu}", 10, 0, 10);
  book<TH1F>("pt_mu", "p_{T}^{#mu} [GeV/c]", 40, 0, 200);
  book<TH1F>("eta_mu", "#eta^{#mu}", 40, -2.1, 2.1);
  book<TH1F>("reliso_mu", "#mu rel. Iso", 40, 0, 0.5);

  // primary vertices
  book<TH1F>("N_pv", "N^{PV}", 50, 0, 50);
}


void UpgradeStudiesGtoWWHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;
  
  std::vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  hist("N_jets")->Fill(Njets, weight);
  
  // begin irene for ratios histograms
  
  auto RecoJetMass = event.topjets->at(0).v4().M();
  auto GenJetMass = event.genjets->at(0).v4().M();
  hist("Mass_Ratio")->Fill((RecoJetMass-GenJetMass)/GenJetMass, weight);


  auto RecoTau21 = event.topjets->at(0).tau2()/event.topjets->at(0).tau1();
  auto GenTau21 = event.gentopjets->at(0).tau2()/event.gentopjets->at(0).tau1();
  hist("Tau21_Gen")->Fill(GenTau21, weight);
   //  hist("Tau21_Reco")->Fill(RecoTau21, weight);
  
  //SoftDrop 
  auto RecoJetSDMass1 = event.topjets->at(0).softdropmass();
  auto GenJetSDMass1 = event.gentopjets->at(0).v4().M();
  hist("SoftDropMass_Gen")->Fill(GenJetSDMass1, weight);
  hist("SoftDropMass_ratio")->Fill((RecoJetSDMass1-GenJetSDMass1)/GenJetSDMass1, weight);
  cout << " RecoJetSDMass1: " << RecoJetSDMass1 << " GenJetSDMass1: " << GenJetSDMass1 << " ratio: " << (RecoJetSDMass1-GenJetSDMass1)/GenJetSDMass1 << endl;

  //CHF 
  //  auto RecoCHF1 = event.topjets->at(0).chargedHadronEnergyFraction();
  //auto GenCHF = event.gentopjets->chf();
  //auto GenCHF1 = event.gentopjets->at(0).chf();
  //cout << " RecoCHF1: " << RecoCHF1 << " GenCHF1: " << GenCHF1 << " ratio: " << (RecoCHF1-GenCHF1)/GenCHF1 << endl;
  //hist("CHF_Gen")->Fill(GenCHF, weight);
  //hist("CHF_Gen_1")->Fill(GenCHF1, weight);
  //hist("CHF_Ratio")->Fill((RecoCHF1-GenCHF1)/GenCHF1, weight);


  //cout << " RecoTau21: " << RecoTau21 << " GenTau21: " << GenTau21 << " ratio: " << (RecoTau21-GenTau21)/RecoTau21 << endl;
  //  hist("Tau_Ratio")->Fill((RecoTau21-GenTau21)/GenTau21, weight);
  //hist("Tau_Ratio")->Fill((RecoTau21-GenTau21)/RecoTau21, weight); 
 //end irene for ratios histograms

  if(Njets>=1){
    hist("eta_jet1")->Fill(jets->at(0).eta(), weight);
  }
  if(Njets>=2){
    hist("eta_jet2")->Fill(jets->at(1).eta(), weight);
  }
  if(Njets>=3){
    hist("eta_jet3")->Fill(jets->at(2).eta(), weight);
  }
  if(Njets>=4){
    hist("eta_jet4")->Fill(jets->at(3).eta(), weight);
  }

  int Nmuons = event.muons->size();
  hist("N_mu")->Fill(Nmuons, weight);
  for (const Muon & thismu : *event.muons){
      hist("pt_mu")->Fill(thismu.pt(), weight);
      hist("eta_mu")->Fill(thismu.eta(), weight);
      hist("reliso_mu")->Fill(thismu.relIso(), weight);
  }
  
  int Npvs = event.pvs->size();
  hist("N_pv")->Fill(Npvs, weight);
}

UpgradeStudiesGtoWWHists::~UpgradeStudiesGtoWWHists(){}
