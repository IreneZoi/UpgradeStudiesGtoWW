#include "UHH2/UpgradeStudiesGtoWW/include/UpgradeStudiesGtoWWSelections.h"
#include "UHH2/core/include/Event.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;

using namespace std;
bool PRINT = false;

DijetSelection::DijetSelection(float dphi_min_, float third_frac_max_): dphi_min(dphi_min_), third_frac_max(third_frac_max_){}
    
bool DijetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
    const auto & jet0 = event.jets->at(0);
    const auto & jet1 = event.jets->at(1);
    auto dphi = deltaPhi(jet0, jet1);
    if(dphi < dphi_min) return false;
    if(event.jets->size() == 2) return true;
    const auto & jet2 = event.jets->at(2);
    auto third_jet_frac = jet2.pt() / (0.5 * (jet0.pt() + jet1.pt()));
    return third_jet_frac < third_frac_max;
}


SDMassSelection::SDMassSelection(float Mass_sd_min_, float Mass_sd_max_): Mass_sd_min(Mass_sd_min_), Mass_sd_max(Mass_sd_max_){}
    
bool SDMassSelection::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                           
  if(PRINT) cout << " asserted topjets" <<endl;

  if(event.topjets->size() < 2) return false;
  std::vector<TopJet> Tjets = *event.topjets;
  if(PRINT) cout << "TopJet" <<endl;
  const auto & jet1 = Tjets[0];
  const auto & jet2 = Tjets[1];
  if(PRINT) cout << "jets" <<endl;
  LorentzVector subjet_sum1;
  LorentzVector subjet_sum2;
  if(PRINT) cout << "lorentz subj" <<endl;

  for (const auto s1 : jet1.subjets()) {
    subjet_sum1 += s1.v4();
  }
  auto JetSDMass1 = subjet_sum1.M();
  if(PRINT) cout << "sd mass 1 " <<endl;
  for (const auto s2 : jet2.subjets()) {
    subjet_sum2 += s2.v4();
  }
  auto JetSDMass2 = subjet_sum2.M();
  if(PRINT) cout << "sd mass 2" <<endl;

  if( JetSDMass1 < Mass_sd_min || JetSDMass2 < Mass_sd_min || JetSDMass1 > Mass_sd_max || JetSDMass2 > Mass_sd_max) return false;
  else return true;



}



LowPtSelection::LowPtSelection(float pt_min_, float pt_max_): pt_min(pt_min_), pt_max(pt_max_){}
    
bool LowPtSelection::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                           
  if(PRINT) cout << " asserted topjets" <<endl;
  if(event.topjets->size() < 1) return false;

  auto pt = event.topjets->at(0).pt();
  if( pt < pt_min || pt > pt_max ) return false;
  else return true;
}

HighPtSelection::HighPtSelection(float pt_min_): pt_min(pt_min_){}
    
bool HighPtSelection::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                           
  if(PRINT) cout << " asserted topjets" <<endl;
  if(event.topjets->size() < 1) return false;

  auto pt = event.topjets->at(0).pt();
  if( pt < pt_min ) return false;
  else return true;



}


