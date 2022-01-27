#include "UHH2/common/include/BTagCalibrationStandalone.h"
#include "UHH2/common/include/MCWeight.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/common/include/Utils.h"
#include <UHH2/common/include/TTbarGen.h>
#include "Riostream.h"
#include "TFile.h"
#include "TH1F.h"

#include <stdexcept>

using namespace uhh2;
using namespace std;

MCLumiWeight::MCLumiWeight(Context & ctx){
  use_sframe_weight = string2bool(ctx.get("use_sframe_weight", "true"));
  if(use_sframe_weight){
    return;
  }
  auto dataset_type = ctx.get("dataset_type");
  bool is_mc = dataset_type == "MC";
  if(!is_mc){
    cout << "Warning: MCLumiWeight will not have an effect on this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
    return;
  } else {
    double dataset_lumi = string2double(ctx.get("dataset_lumi"));
    double reweight_to_lumi = string2double(ctx.get("target_lumi"));
    if(reweight_to_lumi <= 0.0){
      throw runtime_error("MCLumiWeight: target_lumi <= 0.0 not allowed");
    }
    factor = reweight_to_lumi / dataset_lumi;
  }
}

bool MCLumiWeight::process(uhh2::Event & event){
  if(!use_sframe_weight){
    event.weight *= factor;
  }
  return true;
}



MCPileupReweight::MCPileupReweight(Context & ctx, const std::string & sysType):
h_pu_weight_(ctx.declare_event_output<float>("weight_pu")),
h_pu_weight_up_(ctx.declare_event_output<float>("weight_pu_down")),
h_pu_weight_down_(ctx.declare_event_output<float>("weight_pu_up")),
h_npu_data_up(0),
h_npu_data_down(0),
sysType_(sysType)
{
  auto dataset_type = ctx.get("dataset_type");
  bool is_mc = dataset_type == "MC";
  if(!is_mc){
    cout << "Warning: MCPileupReweight will not have an effect on this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
    return;
  }

  //    h_pu_weight_ = ctx.declare_event_output<float>("weight_pu");

  // backward compatibility: (((no tag) is chosen over 25ns) is chosen over 50ns)
  std::string pileup_directory           = ctx.get("pileup_directory",
  ctx.get("pileup_directory_25ns",
  ctx.get("pileup_directory_50ns", "")));
  std::string pileup_directory_data      = ctx.get("pileup_directory_data");
  std::string pileup_directory_data_up   = ctx.get("pileup_directory_data_up", "");
  std::string pileup_directory_data_down = ctx.get("pileup_directory_data_down", "");

  if(pileup_directory_data == ""){
    throw runtime_error("MCPileupReweight: pileup_directory_data is needed!");
  }
  if(pileup_directory == ""){
    throw runtime_error("MCPileupReweight: pileup_directory is needed!");
  }
  if (sysType == "up" && !pileup_directory_data_up.length()) {
    throw runtime_error("MCPileupReweight: pileup_directory_data_up is needed!");
  }
  if (sysType == "down" && !pileup_directory_data_down.length()) {
    throw runtime_error("MCPileupReweight: pileup_directory_data_down is needed!");
  }
  if (sysType != "up" && sysType != "down") {
    sysType_ = "";  // this is checked first in the process function
  }

  TFile file_mc(locate_file(pileup_directory).c_str());
  h_npu_mc   = (TH1F*) file_mc.Get("input_Event/N_TrueInteractions");
  h_npu_mc->SetDirectory(0);
  h_npu_mc->Scale(1./h_npu_mc->Integral());

  TFile file_data(locate_file(pileup_directory_data).c_str());
  h_npu_data = (TH1F*) file_data.Get("pileup");
  h_npu_data->SetDirectory(0);
  h_npu_data->Scale(1./h_npu_data->Integral());

  if(h_npu_mc->GetNbinsX() != h_npu_data->GetNbinsX()){
    throw runtime_error("MCPileupReweight: pile-up histograms for data and MC have different numbers of bins");
  }
  if( (h_npu_mc->GetXaxis()->GetXmax() != h_npu_data->GetXaxis()->GetXmax())
  || (h_npu_mc->GetXaxis()->GetXmin() != h_npu_data->GetXaxis()->GetXmin()))
  {
    throw runtime_error("MCPileupReweight: pile-up histograms for data and MC have different axis ranges");
  }

  if (pileup_directory_data_up.length()) {
    TFile file_data_up(locate_file(pileup_directory_data_up).c_str());
    h_npu_data_up = (TH1F*) file_data_up.Get("pileup");
    h_npu_data_up->SetDirectory(0);
    h_npu_data_up->Scale(1./h_npu_data_up->Integral());
    if(h_npu_mc->GetNbinsX() != h_npu_data_up->GetNbinsX()){
      throw runtime_error("MCPileupReweight: pile-up histograms for data_up and MC have different numbers of bins");
    }
    if( (h_npu_mc->GetXaxis()->GetXmax() != h_npu_data_up->GetXaxis()->GetXmax())
    || (h_npu_mc->GetXaxis()->GetXmin() != h_npu_data_up->GetXaxis()->GetXmin()))
    {
      throw runtime_error("MCPileupReweight: pile-up histograms for data_up and MC have different axis ranges");
    }
  }
  if (pileup_directory_data_down.length()) {
    TFile file_data_down(locate_file(pileup_directory_data_down).c_str());
    h_npu_data_down = (TH1F*) file_data_down.Get("pileup");
    h_npu_data_down->SetDirectory(0);
    h_npu_data_down->Scale(1./h_npu_data_down->Integral());
    if(h_npu_mc->GetNbinsX() != h_npu_data_down->GetNbinsX()){
      throw runtime_error("MCPileupReweight: pile-up histograms for data_down and MC have different numbers of bins");
    }
    if( (h_npu_mc->GetXaxis()->GetXmax() != h_npu_data_down->GetXaxis()->GetXmax())
    || (h_npu_mc->GetXaxis()->GetXmin() != h_npu_data_down->GetXaxis()->GetXmin()))
    {
      throw runtime_error("MCPileupReweight: pile-up histograms for data_down and MC have different axis ranges");
    }
  }
}

bool MCPileupReweight::process(Event &event){
  event.set(h_pu_weight_, 0.f);
  event.set(h_pu_weight_up_, 0.f);
  event.set(h_pu_weight_down_, 0.f);
  if (event.isRealData) {
    event.set(h_pu_weight_, 1.f);
    return true;
  }

  double weight = 0., weight_up = 0., weight_down = 0., trueNumInteractions = 0.;
  // handle scenarios where events fall outside of our histograms
  // esp for 94X MC screwup where -ve # vertices exist

  try{
    trueNumInteractions = event.genInfo->pileup_TrueNumInteractions();
    if (event.genInfo->pileup_TrueNumInteractions() < h_npu_mc->GetXaxis()->GetXmin()) {
      cout << "WARNING trueNumInteractions = " << trueNumInteractions << " < lower edge of MC hist = " << h_npu_mc->GetXaxis()->GetXmin();
      cout << " Setting event weight_pu to 0" << endl;
      return false;
    } else if (event.genInfo->pileup_TrueNumInteractions() > h_npu_mc->GetXaxis()->GetXmax()) {
      cout << "WARNING trueNumInteractions = " << trueNumInteractions << " > upper edge of MC hist = " << h_npu_mc->GetXaxis()->GetXmax();
      cout << " Setting event weight_pu to 0" << endl;
      return false;
    }
  }
  catch(const std::runtime_error& error){
    std::cout<<"Problem with genInfo in MCWeight.cxx"<<std::endl;
    std::cout<<error.what();
  }

  int binnumber = h_npu_mc->GetXaxis()->FindBin(trueNumInteractions);
  auto mc_cont = h_npu_mc->GetBinContent(binnumber);
  if (mc_cont > 0) {
    weight = h_npu_data->GetBinContent(binnumber)/mc_cont;
    event.set(h_pu_weight_, weight);

    if (h_npu_data_up) {
      weight_up = h_npu_data_up->GetBinContent(binnumber)/mc_cont;
      event.set(h_pu_weight_up_, weight_up);
    }

    if (h_npu_data_down) {
      weight_down = h_npu_data_down->GetBinContent(binnumber)/mc_cont;
      event.set(h_pu_weight_down_, weight_down);
    }
  } else {
    cout << "WARNING no value in MC hist for trueNumInteractions = " << trueNumInteractions;
    cout << " Setting event weight_pu to 0" << endl;
    return false;
  }

//  if (sysType_ == "") {
//    event.weight *= weight;
//  } else if (sysType_ == "down") {
//    event.weight *= weight_down;
//  } else {
//    event.weight *= weight_up;
//  }


  return true;
}

MCScaleVariation::MCScaleVariation(Context & ctx){

  auto dataset_type = ctx.get("dataset_type");
  bool is_mc = dataset_type == "MC";
  h_murmuf_weight_upup_     = ctx.declare_event_output<float>("weight_murmuf_upup");
  h_murmuf_weight_upnone_   = ctx.declare_event_output<float>("weight_murmuf_upnone");
  h_murmuf_weight_noneup_   = ctx.declare_event_output<float>("weight_murmuf_noneup");
  h_murmuf_weight_downdown_ = ctx.declare_event_output<float>("weight_murmuf_downdown");
  h_murmuf_weight_downnone_ = ctx.declare_event_output<float>("weight_murmuf_downnone");
  h_murmuf_weight_nonedown_ = ctx.declare_event_output<float>("weight_murmuf_nonedown");

  if(!is_mc){
    cout << "Warning: MCScaleVariation will not have an effect on this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
    return;
  }
  auto s_mu_r = ctx.get("ScaleVariationMuR");
  auto s_mu_f = ctx.get("ScaleVariationMuF");

  if(s_mu_r == "up") {i_mu_r = 1;}
  else if(s_mu_r == "down"){i_mu_r = 2;}

  if(s_mu_f == "up"){i_mu_f = 1;}
  else if(s_mu_f == "down"){i_mu_f = 2;}

}

bool MCScaleVariation::process(Event & event){

  // Set weights to 1 for data
  if (event.isRealData) {
    event.set(h_murmuf_weight_upup_, 1.);
    event.set(h_murmuf_weight_upnone_, 1.);
    event.set(h_murmuf_weight_noneup_, 1.);
    event.set(h_murmuf_weight_downdown_, 1.);
    event.set(h_murmuf_weight_downnone_, 1.);
    event.set(h_murmuf_weight_nonedown_, 1.);
    return true;
  }

  try{
    // Set weights to 1 if no genInfo scale variation weights exist
    if(event.genInfo->systweights().size() < 9){
      event.set(h_murmuf_weight_upup_, 1.);
      event.set(h_murmuf_weight_upnone_, 1.);
      event.set(h_murmuf_weight_noneup_, 1.);
      event.set(h_murmuf_weight_downdown_, 1.);
      event.set(h_murmuf_weight_downnone_, 1.);
      event.set(h_murmuf_weight_nonedown_, 1.);
      return true;
    }

    // Set handles, written for all relevant cases irrespective of the values of mu_r and mu_f specified in the config file
    event.set(h_murmuf_weight_upup_, event.genInfo->systweights().at(4)/event.genInfo->originalXWGTUP());
    event.set(h_murmuf_weight_upnone_, event.genInfo->systweights().at(3)/event.genInfo->originalXWGTUP());
    event.set(h_murmuf_weight_noneup_, event.genInfo->systweights().at(1)/event.genInfo->originalXWGTUP());
    event.set(h_murmuf_weight_downdown_, event.genInfo->systweights().at(8)/event.genInfo->originalXWGTUP());
    event.set(h_murmuf_weight_downnone_, event.genInfo->systweights().at(6)/event.genInfo->originalXWGTUP());
    event.set(h_murmuf_weight_nonedown_, event.genInfo->systweights().at(2)/event.genInfo->originalXWGTUP());

    // Modify event weight according to scale variation specified in config file
    if (i_mu_r == 0 && i_mu_f == 0) return true;
    else if(i_mu_r == 0 && i_mu_f == 1) syst_weight = event.genInfo->systweights().at(1);
    else if(i_mu_r == 0 && i_mu_f == 2) syst_weight = event.genInfo->systweights().at(2);

    else if(i_mu_r == 1 && i_mu_f == 0) syst_weight = event.genInfo->systweights().at(3);
    else if(i_mu_r == 1 && i_mu_f == 1) syst_weight = event.genInfo->systweights().at(4);
    else if(i_mu_r == 1 && i_mu_f == 2) syst_weight = event.genInfo->systweights().at(5);

    else if(i_mu_r == 2 && i_mu_f == 0) syst_weight = event.genInfo->systweights().at(6);
    else if(i_mu_r == 2 && i_mu_f == 1) syst_weight = event.genInfo->systweights().at(7);
    else if(i_mu_r == 2 && i_mu_f == 2) syst_weight = event.genInfo->systweights().at(8);

//    event.weight *= syst_weight/event.genInfo->originalXWGTUP();
  }
  catch(const std::runtime_error& error){
    std::cout<<"Problem with genInfo in MCWeight.cxx"<<std::endl;
    std::cout<<error.what();
  }

  return true;
}


MCToptaggSF::MCToptaggSF(uhh2::Context & ctx,
  const std::string & sf_file_path,
  const std::string & wp_name):
  h_toptagSF_weight_      (ctx.declare_event_output<float>("weight_toptagSF_")),
  h_toptagSF_up_weight_      (ctx.declare_event_output<float>("weight_toptagSF_up_")),
  h_toptagSF_down_weight_      (ctx.declare_event_output<float>("weight_toptagSF_down_"))
  {
 
    h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("AK8PuppiTopTags");
    auto dataset_type = ctx.get("dataset_type");
    bool is_mc = dataset_type == "MC";

    if (!is_mc) {
      cout << "Warning: TopTagScaleFactor will not have an effect on "
      <<" this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
      return;
    }
    string cat_name_1 = "notmerged";
    string cat_name_3 = "mergedTop";
    string cat_name_2 = "semimerged";

    string var_name = "nominal";

/*    TFile sf_file(locate_file(sf_file_path).c_str());
    if (sf_file.IsZombie()) {
      throw runtime_error("Scale factor file for muons not found: " + sf_file_path);
    }

    sf_hist_.reset((TH1*) sf_file.Get("PUPPI_wp4/sf_notmerged_nominal"));
    if (!sf_hist_.get()) {
            throw runtime_error("Scale factor directory not found in file: ");     
    }

    sf_hist2_.reset((TH1*) sf_file.Get((wp_name+"/sf_"+cat_name_2+"_"+var_name).c_str()));
    if (!sf_hist2_.get()) {
            throw runtime_error("Scale factor directory not found in file: ");
    }

    sf_hist3_.reset((TH1*) sf_file.Get((wp_name+"/sf_"+cat_name_3+"_"+var_name).c_str()));
    if (!sf_hist3_.get()) {
            throw runtime_error("Scale factor directory not found in file: ");
    }
*/
  }  

  bool MCToptaggSF::process(uhh2::Event & event) {

  vector<TopJet> TopTags = event.get(h_AK8TopTags);
  event.set(h_toptagSF_weight_, 1.f);
  event.set(h_toptagSF_up_weight_, 1.f);
  event.set(h_toptagSF_down_weight_, 1.f);

  float wgt = 1.;

 //2018
/*
  float mergedTop_nominal_1 = 0.998216957;  float mergedTop_nominal_2 = 0.99866605;  float mergedTop_nominal_3 = 0.98657537;  float mergedTop_nominal_4 = 0.94760686;  float mergedTop_nominal_5 = 0.94760686;
  float mergedTop_up_1 = 1.0100830;  float mergedTop_up_2 = 1.0841380;  float mergedTop_up_3 = 1.0128756;  float mergedTop_up_4 = 0.9817470;  float mergedTop_up_5 = 1.0247426;
  float mergedTop_down_1 = 0.95425612;  float mergedTop_down_2 = 0.97232574;  float mergedTop_down_3 = 0.96027511;  float mergedTop_down_4 = 0.90903896;  float mergedTop_down_5 = 0.87047106;

  float semimerged_nominal_1 = 1.0725051;  float semimerged_nominal_2 = 1.0841380;  float semimerged_nominal_3 = 0.98462087;  float semimerged_nominal_4 = 0.97770125;  float semimerged_nominal_5 = 0.97770125;
  float semimerged_up_1 = 1.1335994;  float semimerged_up_2 = 1.1564199;  float semimerged_up_3 = 1.0751463;  float semimerged_up_4 = 1.0938857;  float semimerged_up_5 = 1.2100700;
  float semimerged_down_1 = 1.0114108;  float semimerged_down_2 = 1.0118561;  float semimerged_down_3 = 0.89409548;  float semimerged_down_4 = 0.86151689;  float semimerged_down_5 = 0.74533248;

  float notmerged_nominal_1 = 1.0812713;  float notmerged_nominal_2 = 1.1675383;  float notmerged_nominal_3 = 1.1273180;  float notmerged_nominal_4 = 1.0532738;  float notmerged_nominal_5 = 1.0532738;
  float notmerged_up_1 = 1.1622297;  float notmerged_up_2 = 1.2429656;  float notmerged_up_3 = 1.2226826;  float notmerged_up_4 = 1.1534973;  float notmerged_up_5 = 1.2537208;
  float notmerged_down_1 = 1.0003129;  float notmerged_down_2 = 1.0921111;  float notmerged_down_3 = 1.0319535;  float notmerged_down_4 = 0.95305032;  float notmerged_down_5 = 0.85282677;
*/

  //2017

  float mergedTop_nominal_1 = 0.98674524;  float mergedTop_nominal_2 =  0.96778202;  float mergedTop_nominal_3 = 0.95883101;  float mergedTop_nominal_4 = 0.93953139;  float mergedTop_nominal_5 = 0.93953139;
  float mergedTop_up_1 = 1.0236051;  float mergedTop_up_2 = 0.99399608;  float mergedTop_up_3 = 0.98822927;  float mergedTop_up_4 = 0.98521435;  float mergedTop_up_5 = 1.0308974;
  float mergedTop_down_1 = 0.94988531;  float mergedTop_down_2 = 0.94156790;  float mergedTop_down_3 = 0.92943281;  float mergedTop_down_4 = 0.89384848;  float mergedTop_down_5 = 0.84816551;

  float semimerged_nominal_1 = 1.0485591;  float semimerged_nominal_2 = 1.0315312;  float semimerged_nominal_3 = 0.96651822;  float semimerged_nominal_4 = 0.99758577;  float semimerged_nominal_5 = 0.99758577;
  float semimerged_up_1 = 1.1176342;  float semimerged_up_2 = 1.1203716;  float semimerged_up_3 = 1.0671948;  float semimerged_up_4 = 1.1342028;  float semimerged_up_5 = 1.2708199;
  float semimerged_down_1 = 0.97948390;  float semimerged_down_2 = 0.94269073;  float semimerged_down_3 = 0.86584157;  float semimerged_down_4 = 0.86096877;  float semimerged_down_5 = 0.72435170;

  float notmerged_nominal_1 = 1.1613269;  float notmerged_nominal_2 = 1.0389098;  float notmerged_nominal_3 = 1.0157162;  float notmerged_nominal_4 = 1.0329711;  float notmerged_nominal_5 = 1.0329711;
  float notmerged_up_1 = 1.2725911;  float notmerged_up_2 = 1.1417377;  float notmerged_up_3 = 1.1264046;  float notmerged_up_4 = 1.1556237;  float notmerged_up_5 = 1.2782762;
  float notmerged_down_1 = 1.0500627;  float notmerged_down_2 = 0.93608177;  float notmerged_down_3 = 0.90502769;  float notmerged_down_4 = 0.91031861;  float notmerged_down_5 = 0.78766608;


  //2016
/*
  float mergedTop_nominal_1 = 0.98623419;  float mergedTop_nominal_2 = 0.96503079;  float mergedTop_nominal_3 = 1.0029691;  float mergedTop_nominal_4 = 1.0236728;  float mergedTop_nominal_5 = 1.0236728;
  float mergedTop_up_1 = 1.0226288;  float mergedTop_up_2 = 0.99043179;  float mergedTop_up_3 = 1.0344294;  float mergedTop_up_4 = 1.0716326;  float mergedTop_up_5 = 1.1195925;
  float mergedTop_down_1 = 0.94983965;  float mergedTop_down_2 = 0.93962979;  float mergedTop_down_3 = 0.97150880;  float mergedTop_down_4 = 0.97571295;  float mergedTop_down_5 = 0.92775309;

  float semimerged_nominal_1 = 0.95853740;  float semimerged_nominal_2 = 0.98230469;  float semimerged_nominal_3 = 0.98299700;  float semimerged_nominal_4 = 1.0720320;  float semimerged_nominal_5 = 1.0720320;
  float semimerged_up_1 = 1.0212306;  float semimerged_up_2 = 1.0599980;  float semimerged_up_3 = 1.0708913;  float semimerged_up_4 = 1.1870658;  float semimerged_up_5 = 1.3020997;
  float semimerged_down_1 = 0.89584416;  float semimerged_down_2 = 0.90461129;  float semimerged_down_3 = 0.89510280;  float semimerged_down_4 = 0.95699805;  float semimerged_down_5 = 0.84196419;

  float notmerged_nominal_1 = 1.1884536;  float notmerged_nominal_2 = 1.1685629;  float notmerged_nominal_3 = 1.0916884;  float notmerged_nominal_4 = 1.0678115;  float notmerged_nominal_5 = 1.0678115;
  float notmerged_up_1 = 1.2784989;  float notmerged_up_2 = 1.2864507;  float notmerged_up_3 = 1.2179689;  float notmerged_up_4 = 1.1900523;  float notmerged_up_5 = 1.3122932;
  float notmerged_down_1 = 1.0984082;  float notmerged_down_2 = 1.0506749;  float notmerged_down_3 = 0.96540791;  float notmerged_down_4 = 0.94557053;  float notmerged_down_5 = 0.82332963;
*/
  ///////////////////////////////////

  float wgt_up = 1.;
  float wgt_down = 1.;

  if (event.isRealData) return true;

  assert(event.genparticles);

  //Loop over genparticles
  for(const auto & gp : *event.genparticles){
    //Get tops
    if(fabs(gp.pdgId()) == 6){

      //Get b and W
      auto b = gp.daughter(event.genparticles,1);
      auto W = gp.daughter(event.genparticles,2);
      if(fabs(W->pdgId()) == 5 && fabs(b->pdgId()) == 24){
        b = gp.daughter(event.genparticles,2);
        W = gp.daughter(event.genparticles,1);
      }

      if(abs(W->pdgId()) != 24) {
        for(unsigned int j = 0; j < event.genparticles->size(); ++j) {
          const GenParticle & genp = event.genparticles->at(j);
          auto m1 = genp.mother(event.genparticles, 1);
          auto m2 = genp.mother(event.genparticles, 2);
          bool has_top_mother = ((m1 && m1->index() == gp.index()) || (m2 && m2->index() == gp.index()));
          if(has_top_mother && (abs(genp.pdgId()) == 24)) {
            W = &genp;
            break;
          }
        }
      }
      if(abs(b->pdgId()) != 5 && abs(b->pdgId()) != 3 && abs(b->pdgId()) != 1) {
        for(unsigned int j = 0; j < event.genparticles->size(); ++j) {
          const GenParticle & genp = event.genparticles->at(j);
          auto m1 = genp.mother(event.genparticles, 1);
          auto m2 = genp.mother(event.genparticles, 2);
          bool has_top_mother = ((m1 && m1->index() == gp.index()) || (m2 && m2->index() == gp.index()));
          if(has_top_mother && (abs(genp.pdgId()) == 5 || abs(genp.pdgId()) == 3 || abs(genp.pdgId()) == 1)) {
            b = &genp;
            break;
          }
        }
      }
      if(!((fabs(b->pdgId()) == 5 || fabs(b->pdgId()) == 3 || fabs(b->pdgId()) == 1) && fabs(W->pdgId()) == 24)) return false;

      //To identify decay type, check ID of W daughters
      auto Wd1 = W->daughter(event.genparticles,1);
      auto Wd2 = W->daughter(event.genparticles,2);

      //hadronic
      if(fabs(Wd1->pdgId()) < 7 && fabs(Wd2->pdgId()) < 7){

        for(const TopJet & toptag : TopTags){
 
          float pt_probeJet_ = toptag.pt();      

          int Nmatch = 0;
          if(deltaR(*b, toptag) < 0.8) ++Nmatch;
          if(deltaR(*Wd1, toptag) < 0.8) ++Nmatch;
          if(deltaR(*Wd2, toptag) < 0.8) ++Nmatch;
    
          int bin = 1;

          if(pt_probeJet_ < 400) bin = 1;
          if(pt_probeJet_ >= 400 && pt_probeJet_ < 480) bin = 2;
          if(pt_probeJet_ >= 480 && pt_probeJet_ < 600) bin = 3;
          if(pt_probeJet_ >= 600 && pt_probeJet_ < 1000) bin = 4;
          if(pt_probeJet_ >= 1000) bin = 5;


          if (Nmatch < 2) {
                if(bin == 1){ wgt *= notmerged_nominal_1; wgt_up *= notmerged_up_1; wgt_down *= notmerged_down_1; }
                if(bin == 2){ wgt *= notmerged_nominal_2; wgt_up *= notmerged_up_2; wgt_down *= notmerged_down_2; }
                if(bin == 3){ wgt *= notmerged_nominal_3; wgt_up *= notmerged_up_3; wgt_down *= notmerged_down_3; }
                if(bin == 4){ wgt *= notmerged_nominal_4; wgt_up *= notmerged_up_4; wgt_down *= notmerged_down_4; }
                if(bin == 5){ wgt *= notmerged_nominal_5; wgt_up *= notmerged_up_5; wgt_down *= notmerged_down_5; }
          }
          if (Nmatch == 2) {
                if(bin == 1){ wgt *= semimerged_nominal_1; wgt_up *= semimerged_up_1; wgt_down *= semimerged_down_1; }
                if(bin == 2){ wgt *= semimerged_nominal_2; wgt_up *= semimerged_up_2; wgt_down *= semimerged_down_2; }
                if(bin == 3){ wgt *= semimerged_nominal_3; wgt_up *= semimerged_up_3; wgt_down *= semimerged_down_3; }
                if(bin == 4){ wgt *= semimerged_nominal_4; wgt_up *= semimerged_up_4; wgt_down *= semimerged_down_4; }
                if(bin == 5){ wgt *= semimerged_nominal_5; wgt_up *= semimerged_up_5; wgt_down *= semimerged_down_5; }
          }
          if (Nmatch == 3) {
                if(bin == 1){ wgt *= mergedTop_nominal_1; wgt_up *= mergedTop_up_1; wgt_down *= mergedTop_down_1; }
                if(bin == 2){ wgt *= mergedTop_nominal_2; wgt_up *= mergedTop_up_2; wgt_down *= mergedTop_down_2; }
                if(bin == 3){ wgt *= mergedTop_nominal_3; wgt_up *= mergedTop_up_3; wgt_down *= mergedTop_down_3; }
                if(bin == 4){ wgt *= mergedTop_nominal_4; wgt_up *= mergedTop_up_4; wgt_down *= mergedTop_down_4; }
                if(bin == 5){ wgt *= mergedTop_nominal_5; wgt_up *= mergedTop_up_5; wgt_down *= mergedTop_down_5; }
          }

       }
      }
   }  
 }


 event.set(h_toptagSF_weight_,wgt);
 event.set(h_toptagSF_up_weight_,wgt_up);
 event.set(h_toptagSF_down_weight_,wgt_down);

 return true;
 } 

MCMuonScaleFactor::MCMuonScaleFactor(uhh2::Context & ctx,
  const std::string & sf_file_path,
  const std::string & sf_name,
  float sys_error_percantage,
  const std::string & weight_postfix,
  bool etaYaxis,
  const std::string & sys_uncert,
  const std::string & muons_handle_name):
  h_muons_            (ctx.get_handle<std::vector<Muon>>(muons_handle_name)),
  h_muon_weight_      (ctx.declare_event_output<float>("weight_sfmu_" + weight_postfix)),
  h_muon_weight_up_   (ctx.declare_event_output<float>("weight_sfmu_" + weight_postfix + "_up")),
  h_muon_weight_down_ (ctx.declare_event_output<float>("weight_sfmu_" + weight_postfix + "_down")),
  sys_error_factor_(sys_error_percantage/100.), etaYaxis_(etaYaxis)
  {

    auto dataset_type = ctx.get("dataset_type");
    bool is_mc = dataset_type == "MC";
    if (!is_mc) {
      cout << "Warning: MCMuonScaleFactor will not have an effect on "
      <<" this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
      return;
    }

    TFile sf_file(locate_file(sf_file_path).c_str());
    if (sf_file.IsZombie()) {
      throw runtime_error("Scale factor file for muons not found: " + sf_file_path);
    }

    sf_hist_.reset((TH2*) sf_file.Get((sf_name + "/abseta_pt").c_str()));
    if (!sf_hist_.get()) {
      sf_hist_.reset((TH2*) sf_file.Get((sf_name + "/abseta_pt_ratio").c_str()));
      if (!sf_hist_.get()) {
        sf_hist_.reset((TH2*) sf_file.Get((sf_name + "/abseta_pair_newTuneP_probe_pt").c_str()));
        if (!sf_hist_.get()) {
          sf_hist_.reset((TH2*) sf_file.Get((sf_name).c_str()));
          if (!sf_hist_.get()) {
            throw runtime_error("Scale factor directory not found in file: " + sf_name);
          }
        }
      }
    }

    sf_hist_->SetDirectory(0);
    if(etaYaxis_){
      eta_min_ = sf_hist_->GetYaxis()->GetXmin();
      eta_max_ = sf_hist_->GetYaxis()->GetXmax();
      pt_min_  = sf_hist_->GetXaxis()->GetXmin();
      pt_max_  = sf_hist_->GetXaxis()->GetXmax();
    }
    else{
      eta_min_ = sf_hist_->GetXaxis()->GetXmin();
      eta_max_ = sf_hist_->GetXaxis()->GetXmax();
      pt_min_  = sf_hist_->GetYaxis()->GetXmin();
      pt_max_  = sf_hist_->GetYaxis()->GetXmax();
    }
    sys_direction_ = 0;
    if (sys_uncert == "up") {
      sys_direction_ = 1;
    } else if (sys_uncert == "down") {
      sys_direction_ = -1;
    }
  }

  bool MCMuonScaleFactor::process(uhh2::Event & event) {

    if (!sf_hist_) {
      event.set(h_muon_weight_,       1.);
      event.set(h_muon_weight_up_,    1.);
      event.set(h_muon_weight_down_,  1.);
      return true;
    }

    const auto & muons = event.get(h_muons_);
    float weight = 1., weight_up = 1., weight_down = 1.;
    for (const auto & mu : muons) {
      float eta = fabs(mu.eta());
      float pt = mu.pt();
      if (eta_min_ < eta && eta_max_ > eta){
        bool out_of_range = false;
        //take scale factor from the last measured pT bin in case of too large/small pT
        if(pt_min_ >= pt) {
          pt=pt_min_+0.0001;
          out_of_range = true;
        }
        if(pt_max_ <= pt) {
          pt=pt_max_-0.0001;
          out_of_range = true;
        }

        int bin;
        if(etaYaxis_) bin = sf_hist_->FindFixBin(pt, eta);
        else          bin = sf_hist_->FindFixBin(eta, pt);

        float w   = sf_hist_->GetBinContent(bin);
        float err = sf_hist_->GetBinError(bin);

        if (w==1 and err==0) {
          if (bin==1) bin +=1;
          else bin -= 1;
          w   = sf_hist_->GetBinContent(bin);
          err = sf_hist_->GetBinError(bin);
        }

        float err_tot = sqrt(err*err + pow(w*sys_error_factor_, 2));
        //take twice the uncertainty if the pT is outside the measured pT range
        if(out_of_range) err_tot*=2;

        weight      *= w;
        weight_up   *= w + err_tot;
        weight_down *= w - err_tot;
      }

    }


    event.set(h_muon_weight_,       weight);
    event.set(h_muon_weight_up_,    weight_up);
    event.set(h_muon_weight_down_,  weight_down);

//    if (sys_direction_ == 1) {
//      event.weight *= weight_up;
//    } else if (sys_direction_ == -1) {
//      event.weight *= weight_down;
//    } else {
//      event.weight *= weight;
//    }

    return true;
  }


  bool MCMuonScaleFactor::process_onemuon(uhh2::Event & event, int i) {

    if (!sf_hist_) {
      event.set(h_muon_weight_,       1.);
      event.set(h_muon_weight_up_,    1.);
      event.set(h_muon_weight_down_,  1.);
      return true;
    }

    const auto & muons = event.get(h_muons_);
    float weight = 1., weight_up = 1., weight_down = 1.;
    Muon mu = muons.at(i);
    float eta = fabs(mu.eta());
    float pt = mu.pt();
    if (eta_min_ < eta && eta_max_ > eta){
      bool out_of_range = false;
      //take scale factor from the last measured pT bin in case of too large/small pT
      if(pt_min_ >= pt) {
        pt=pt_min_+0.0001;
        out_of_range = true;
      }
      if(pt_max_ <= pt) {
        pt=pt_max_-0.0001;
        out_of_range = true;
      }

      int bin;
      if(etaYaxis_)
      bin       = sf_hist_->FindFixBin(pt, eta);
      else
      bin       = sf_hist_->FindFixBin(eta, pt);

      float w       = sf_hist_->GetBinContent(bin);
      float err     = sf_hist_->GetBinError(bin);

      if (w==1 and err==0) {
        if (bin==1) bin +=1;
        else bin -= 1;
        w   = sf_hist_->GetBinContent(bin);
        err = sf_hist_->GetBinError(bin);
      }

      float err_tot = sqrt(err*err + pow(w*sys_error_factor_, 2));
      //take twice the uncertainty if the pT is outside the measured pT range
      if(out_of_range) err_tot*=2;

      weight      *= w;
      weight_up   *= w + err_tot;
      weight_down *= w - err_tot;

    }


    event.set(h_muon_weight_,       weight);
    event.set(h_muon_weight_up_,    weight_up);
    event.set(h_muon_weight_down_,  weight_down);

//    if (sys_direction_ == 1) {
//      event.weight *= weight_up;
//    } else if (sys_direction_ == -1) {
//      event.weight *= weight_down;
//    } else {
//      event.weight *= weight;
//    }

    return true;
  }


  MCMuonTrkScaleFactor::MCMuonTrkScaleFactor(uhh2::Context & ctx,
    const std::string & sf_file_path,
    float sys_error_percantage,
    const std::string & weight_postfix,
    const std::string & sys_uncert,
    const std::string & muons_handle_name):
    h_muons_            (ctx.get_handle<std::vector<Muon>>(muons_handle_name)),
    h_muontrk_weight_      (ctx.declare_event_output<float>("weight_sfmu_" + weight_postfix)),
    h_muontrk_weight_up_   (ctx.declare_event_output<float>("weight_sfmu_" + weight_postfix + "_up")),
    h_muontrk_weight_down_ (ctx.declare_event_output<float>("weight_sfmu_" + weight_postfix + "_down")),
    sys_error_factor_(sys_error_percantage/100.)
    {
      auto dataset_type = ctx.get("dataset_type");
      bool is_mc = dataset_type == "MC";
      if (!is_mc) {
        cout << "Warning: MCMuonTrkScaleFactor will not have an effect on "
        <<" this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
        return;
      }


      std::ifstream in;
      in.open(sf_file_path.c_str());
      Int_t nlines = 0;
      double eta_min,eta_max,eta_ave,factor, err_dn, err_up;

      eta_min_ = 5;
      eta_max_ = -5;
      while (1) {
        in >> eta_min >> eta_ave >> eta_max >> factor >> err_dn >> err_up;
        if (!in.good()) break;
        eta_.push_back(eta_max);
        SFs_.push_back(factor);
        SFs_err_dn_.push_back(err_dn);
        SFs_err_up_.push_back(err_up);
        if(eta_min_>eta_min) eta_min_ = eta_min;
        if(eta_max_<eta_max) eta_max_ = eta_max;
        nlines++;
      }
      in.close();
      //printf("MuonTrk SF: found %d points\n",nlines);

      sys_direction_ = 0;
      if (sys_uncert == "up") {
        sys_direction_ = 1;
      } else if (sys_uncert == "down") {
        sys_direction_ = -1;
      }
    }

    bool MCMuonTrkScaleFactor::process(uhh2::Event & event) {

      // if (!sf_hist_) {
      event.set(h_muontrk_weight_,       1.);
      event.set(h_muontrk_weight_up_,    1.);
      event.set(h_muontrk_weight_down_,  1.);
      //   return true;
      // }

      const auto & muons = event.get(h_muons_);
      float weight = 1., weight_up = 1., weight_down = 1.;
      for (const auto & mu : muons) {
        float eta = fabs(mu.eta());
        float pt = mu.pt();
        if(pt<10.){
          std::cout<<"For muons with pt<10 another input file with SFs should be used!"<<std::endl;
          return true;
        }

        if (eta_min_ < eta && eta_max_ > eta){
          //      bool out_of_range = false;
          for(unsigned int i=1;i<eta_.size();i++){
            if(eta<=eta_[i] && eta>=eta_[i-1]){
              float w = 0.01*SFs_[i];
              float err_dn =  0.01*SFs_err_dn_[i];
              float err_up =  0.01*SFs_err_up_[i];
              weight      *= w;
              weight_up   *= w + fabs(err_up);
              weight_down *= w - fabs(err_dn);
            }
          }
        }
      }
      event.set(h_muontrk_weight_,       weight);
      event.set(h_muontrk_weight_up_,    weight_up);
      event.set(h_muontrk_weight_down_,  weight_down);

//      if (sys_direction_ == 1) {
//        event.weight *= weight_up;
//      } else if (sys_direction_ == -1) {
//        event.weight *= weight_down;
//      } else {
//        event.weight *= weight;
//      }

      return true;
    }



    MCElecScaleFactor::MCElecScaleFactor(uhh2::Context & ctx,
      const std::string & sf_file_path,
      float sys_error_percantage,
      const std::string & weight_postfix,
      const std::string & sys_uncert,
      const std::string & elecs_handle_name,
      const std::string & sf_name):
      h_elecs_            (ctx.get_handle<std::vector<Electron>>(elecs_handle_name)),
      h_elec_weight_      (ctx.declare_event_output<float>("weight_sfelec_" + weight_postfix)),
      h_elec_weight_up_   (ctx.declare_event_output<float>("weight_sfelec_" + weight_postfix + "_up")),
      h_elec_weight_down_ (ctx.declare_event_output<float>("weight_sfelec_" + weight_postfix + "_down")),
      sys_error_factor_(sys_error_percantage/100.)
      {
        auto dataset_type = ctx.get("dataset_type");
        bool is_mc = dataset_type == "MC";
        if (!is_mc) {
          cout << "Warning: MCElecScaleFactor will not have an effect on "
          <<" this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
          return;
        }

        TFile sf_file(locate_file(sf_file_path).c_str());
        if (sf_file.IsZombie()) {
          throw runtime_error("Scale factor file for electrons not found: " + sf_file_path);
        }

        sf_hist_.reset((TH2*) sf_file.Get(sf_name.c_str()));
        if (!sf_hist_.get()) {
          throw runtime_error("Electron scale factor histogram not found in file");
        }
        sf_hist_->SetDirectory(0);
        eta_min_ = sf_hist_->GetXaxis()->GetXmin();
        eta_max_ = sf_hist_->GetXaxis()->GetXmax();
        pt_min_  = sf_hist_->GetYaxis()->GetXmin();
        pt_max_  = sf_hist_->GetYaxis()->GetXmax();

        sys_direction_ = 0;
        if (sys_uncert == "up") {
          sys_direction_ = 1;
        } else if (sys_uncert == "down") {
          sys_direction_ = -1;
        }
      }

      bool MCElecScaleFactor::process(uhh2::Event & event) {

        if (!sf_hist_) {
          event.set(h_elec_weight_,       1.);
          event.set(h_elec_weight_up_,    1.);
          event.set(h_elec_weight_down_,  1.);
          return true;
        }
        const auto & elecs = event.get(h_elecs_);
        float weight = 1., weight_up = 1., weight_down = 1.;
        for (const auto & el : elecs) {
          float eta = fabs(el.supercluster_eta());
          float pt = el.pt();
          if (eta_min_ < eta && eta_max_ > eta){
            bool out_of_range = false;
            //take scale factor from the last measured pT bin in case of too large/small pT
            if(pt_min_ >= pt) {
              pt=pt_min_+0.0001;
              out_of_range = true;
            }
            if(pt_max_ <= pt) {
              pt=pt_max_-0.0001;
              out_of_range = true;
            }
            int bin       = sf_hist_->FindFixBin(eta, pt);
            float w       = sf_hist_->GetBinContent(bin);
            float err     = sf_hist_->GetBinError(bin);

            if (w==1 and err==0) {
              if (bin==1) bin +=1;
              else bin -= 1;
              w   = sf_hist_->GetBinContent(bin);
              err = sf_hist_->GetBinError(bin);
            }

            float err_tot = sqrt(err*err + pow(w*sys_error_factor_, 2));
            //take twice the uncertainty if the pT is outside the measured pT range
            if(out_of_range) err_tot*=2;

            weight      *= w;
            weight_up   *= w + err_tot;
            weight_down *= w - err_tot;
          }

        }

        event.set(h_elec_weight_,       weight);
        event.set(h_elec_weight_up_,    weight_up);
        event.set(h_elec_weight_down_,  weight_down);

//        if (sys_direction_ == 1) {
//          event.weight *= weight_up;
//        } else if (sys_direction_ == -1) {
//          event.weight *= weight_down;
//        } else {
//          event.weight *= weight;
//        }

        return true;
      }


    MCNjetsHTScaleFactor::MCNjetsHTScaleFactor(uhh2::Context & ctx,
      const std::string & sf_file_path,
      float sys_error_percantage,
      const std::string & weight_postfix,
      const std::string & sys_uncert,
      const std::string & elecs_handle_name,
      const std::string & sf_name):
      h_elecs_            (ctx.get_handle<std::vector<Electron>>(elecs_handle_name)),
      h_HT_weight_	  (ctx.declare_event_output<float>("weight_HT_" + weight_postfix)),
      h_HT_weight_up_   (ctx.declare_event_output<float>("weight_HT_" + weight_postfix + "_up")),
      h_HT_weight_down_ (ctx.declare_event_output<float>("weight_HT_" + weight_postfix + "_down")),
      sys_error_factor_(sys_error_percantage/100.)
      {
//        bool isMuon = false; bool isElectron = false;
//        if(ctx.get("channel") == "muon") isMuon = true;
//        if(ctx.get("channel") == "electron") isElectron = true;
       	auto dataset_type = ctx.get("dataset_type");
        bool is_mc = dataset_type == "MC";
        if (!is_mc) {
          return;
        }

	TFile sf_file(locate_file(sf_file_path).c_str());
        if (sf_file.IsZombie()) {
          throw runtime_error("Scale factor file for electrons not found: " + sf_file_path);
        }

	sf_hist_boosted_.reset((TH2*) sf_file.Get("D_boosted"));
//        sf_hist_semiresolved_.reset((TH2*) sf_file.Get("D_semiresolved"));
//        sf_hist_resolved_.reset((TH2*) sf_file.Get("D_resolved"));

        if (!sf_hist_boosted_.get()) {
          throw runtime_error("HT scale factor histogram not found in file");
        }
//        if (!sf_hist_semiresolved_.get()) {
//          throw runtime_error("HT scale factor histogram not found in file");
//        }
//        if (!sf_hist_resolved_.get()) {
//          throw runtime_error("HT scale factor histogram not found in file");
//        }

	sf_hist_boosted_->SetDirectory(0);
//        sf_hist_semiresolved_->SetDirectory(0);
//        sf_hist_resolved_->SetDirectory(0);        

        sys_direction_ = 0;
        if (sys_uncert == "up") {
          sys_direction_ = 1;
        } else if (sys_uncert == "down") {
          sys_direction_ = -1;
        }
      }

      bool MCNjetsHTScaleFactor::process(uhh2::Event & event) {

        if (!sf_hist_boosted_) {
          event.set(h_HT_weight_,	  1.);
          event.set(h_HT_weight_up_,    1.);
          event.set(h_HT_weight_down_,  1.);
          return true;
        }

	const auto & elecs = event.get(h_elecs_);
        vector<Jet>* Ak4jets = event.jets;
        vector<Muon>* muon = event.muons;
        vector<Electron>* el = event.electrons;
        int NAk4jets = Ak4jets->size();
        double met = event.met->pt();
        double pt_lep = 0.;
        if(muon->size() > 0) pt_lep = event.muons->at(0).pt();
        if(el->size() > 0) pt_lep = event.electrons->at(0).pt();
        double HT = met + pt_lep;
       
        float weight = 1., weight_up = 1., weight_down = 1.;

        
        if (0 < HT && 1200 > HT){
            bool out_of_range = false;

            if(1 >= NAk4jets) {
              NAk4jets=2;
              out_of_range = true;
            }
            if(12 <= NAk4jets) {
              NAk4jets=12;
              out_of_range = true;
            }
            int bin	  = sf_hist_boosted_->FindFixBin(NAk4jets, HT);
            float w	  = sf_hist_boosted_->GetBinContent(bin);
            float err     = sf_hist_boosted_->GetBinError(bin);

            if (w==1 and err==0) {
              if (bin==1) bin +=1;
              else bin -= 1;
              w   = sf_hist_boosted_->GetBinContent(bin);
              err = sf_hist_boosted_->GetBinError(bin);
            }

            float err_tot = sqrt(err*err + pow(w*sys_error_factor_, 2));
            if(out_of_range) err_tot*=2;

            weight	*= w;
            weight_up   *= w + err_tot;
            weight_down *= w - err_tot;
        }


	event.set(h_HT_weight_,	weight);
        event.set(h_HT_weight_up_,    weight_up);
        event.set(h_HT_weight_down_,  weight_down);

//        if (sys_direction_ == 1) {
//          event.weight *= weight_up;
//        } else if (sys_direction_ == -1) {
//          event.weight *= weight_down;
//        } else {
//          event.weight *= weight;
//        }

	return true;
      }


      MCBTagScaleFactor::MCBTagScaleFactor(uhh2::Context & ctx,
        BTag::algo tagger,
        BTag::wp wp,
        const std::string & jets_handle_name,
        const std::string & sysType,
        const std::string & measType_bc,
        const std::string & measType_udsg,
        const std::string & xml_param_name,
        const std::string & weights_name_postfix,
        const std::string & xml_calib_name):
        btag_(BTag(tagger, wp)),
        h_jets_(ctx.get_handle<std::vector<Jet>>(jets_handle_name)),
        h_topjets_(ctx.get_handle<std::vector<TopJet>>(jets_handle_name)),
        sysType_(sysType),
        h_btag_weight_          (ctx.declare_event_output<float>("weight_btag"+weights_name_postfix)),
        h_btag_weight_up_       (ctx.declare_event_output<float>("weight_btag_up"+weights_name_postfix)),
        h_btag_weight_down_     (ctx.declare_event_output<float>("weight_btag_down"+weights_name_postfix)),
        h_btag_weight_bc_up_    (ctx.declare_event_output<float>("weight_btag_bc_up"+weights_name_postfix)),
        h_btag_weight_bc_down_  (ctx.declare_event_output<float>("weight_btag_bc_down"+weights_name_postfix)),
        h_btag_weight_udsg_up_  (ctx.declare_event_output<float>("weight_btag_udsg_up"+weights_name_postfix)),
        h_btag_weight_udsg_down_(ctx.declare_event_output<float>("weight_btag_udsg_down"+weights_name_postfix)),
        h_btag_weight_bc_up_un_    (ctx.declare_event_output<float>("weight_btag_bc_up_un"+weights_name_postfix)),
        h_btag_weight_bc_down_un_  (ctx.declare_event_output<float>("weight_btag_bc_down_un"+weights_name_postfix)),
        h_btag_weight_udsg_up_un_  (ctx.declare_event_output<float>("weight_btag_udsg_up_un"+weights_name_postfix)),
        h_btag_weight_udsg_down_un_(ctx.declare_event_output<float>("weight_btag_udsg_down_un"+weights_name_postfix))
        {
          auto dataset_type = ctx.get("dataset_type");
          bool is_mc = dataset_type == "MC";
          if (!is_mc) {
            cout << "Warning: MCBTagScaleFactor will not have an effect on "
            <<" this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
            return;
          }

          TFile eff_file(locate_file(ctx.get(xml_param_name)).c_str());
          if (eff_file.IsZombie()) {
            cout << "Warning: MCBTagScaleFactor will not have an effect because the root-file "
            << "with MC-efficiencies not found: " << ctx.get(xml_param_name) << endl;
            eff_file.Close();
            return;
          }
          eff_b_.reset((TH2*) eff_file.Get("BTagMCEffFlavBEff"));
          eff_c_.reset((TH2*) eff_file.Get("BTagMCEffFlavCEff"));
          eff_udsg_.reset((TH2*) eff_file.Get("BTagMCEffFlavUDSGEff"));
          eff_b_->SetDirectory(0);
          eff_c_->SetDirectory(0);
          eff_udsg_->SetDirectory(0);
          eff_file.Close();

          // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagCalibration
          BTagCalibration calib_data(btag_.GetTagger(), ctx.get(xml_calib_name));
          BTagEntry::OperatingPoint op = (BTagEntry::OperatingPoint) btag_.GetWorkingPoint();

          calib_up_.reset(new BTagCalibrationReader(op, "up_correlated"));
          calib_.reset(new BTagCalibrationReader(op, "central"));
          calib_down_.reset(new BTagCalibrationReader(op, "down_correlated"));
//Nuevp!!!!!!!!!!
          calib_up_un_.reset(new BTagCalibrationReader(op, "up_uncorrelated"));
          calib_down_un_.reset(new BTagCalibrationReader(op, "down_uncorrelated"));
//!!!!!!!!!!!!!
          calib_up_->load(calib_data, BTagEntry::FLAV_B, measType_bc);
          calib_up_->load(calib_data, BTagEntry::FLAV_C, measType_bc);
          calib_up_->load(calib_data, BTagEntry::FLAV_UDSG, measType_udsg);
          calib_->load(calib_data, BTagEntry::FLAV_B, measType_bc);
          calib_->load(calib_data, BTagEntry::FLAV_C, measType_bc);
          calib_->load(calib_data, BTagEntry::FLAV_UDSG, measType_udsg);
          calib_down_->load(calib_data, BTagEntry::FLAV_B, measType_bc);
          calib_down_->load(calib_data, BTagEntry::FLAV_C, measType_bc);
          calib_down_->load(calib_data, BTagEntry::FLAV_UDSG, measType_udsg);
//!!!!!!!
          calib_up_un_->load(calib_data, BTagEntry::FLAV_B, measType_bc);
          calib_up_un_->load(calib_data, BTagEntry::FLAV_C, measType_bc);
          calib_up_un_->load(calib_data, BTagEntry::FLAV_UDSG, measType_udsg);
          calib_down_un_->load(calib_data, BTagEntry::FLAV_B, measType_bc);
          calib_down_un_->load(calib_data, BTagEntry::FLAV_C, measType_bc);
          calib_down_un_->load(calib_data, BTagEntry::FLAV_UDSG, measType_udsg);
//!!!!!!!!

       }

        bool MCBTagScaleFactor::process(Event & event) {

          if (!calib_) {
            event.set(h_btag_weight_,           1.);
            event.set(h_btag_weight_up_,        1.);
            event.set(h_btag_weight_down_,      1.);
            event.set(h_btag_weight_bc_up_,     1.);
            event.set(h_btag_weight_bc_down_,   1.);
            event.set(h_btag_weight_udsg_up_,   1.);
            event.set(h_btag_weight_udsg_down_, 1.);
            event.set(h_btag_weight_bc_up_un_,     1.);
            event.set(h_btag_weight_bc_down_un_,   1.);
            event.set(h_btag_weight_udsg_up_un_,   1.);
            event.set(h_btag_weight_udsg_down_un_, 1.);
            return true;
          }

          float weight, weightErrBC, weightErrUDSG, weightErrBC_un, weightErrUDSG_un;
          if (event.is_valid(h_topjets_)) {
            std::tie(weight, weightErrBC, weightErrUDSG, weightErrBC_un, weightErrUDSG_un) = get_weight_btag(event.get(h_topjets_), event);
          } else {
            assert(event.is_valid(h_jets_));
            TopJet tj;
            tj.set_subjets(event.get(h_jets_));
            std::tie(weight, weightErrBC, weightErrUDSG, weightErrBC_un, weightErrUDSG_un) = get_weight_btag(vector<TopJet>({tj}), event);
          }
          float weightErr = sqrt(weightErrBC*weightErrBC + weightErrUDSG*weightErrUDSG);

          float weight_up        = weight + weightErr;
          float weight_down      = weight - weightErr;
          float weight_bc_up     = weight + weightErrBC;
          float weight_bc_down   = weight - weightErrBC;
          float weight_udsg_up   = weight + weightErrUDSG;
          float weight_udsg_down = weight - weightErrUDSG;

          float weight_bc_up_un     = weight + weightErrBC_un;
          float weight_bc_down_un   = weight - weightErrBC_un;
          float weight_udsg_up_un   = weight + weightErrUDSG_un;
          float weight_udsg_down_un = weight - weightErrUDSG_un;


          event.set(h_btag_weight_,           weight);
          event.set(h_btag_weight_up_,        weight_up);
          event.set(h_btag_weight_down_,      weight_down);
          event.set(h_btag_weight_bc_up_,     weight_bc_up);
          event.set(h_btag_weight_bc_down_,   weight_bc_down);
          event.set(h_btag_weight_udsg_up_,   weight_udsg_up);
          event.set(h_btag_weight_udsg_down_, weight_udsg_down);

          event.set(h_btag_weight_bc_up_un_,     weight_bc_up_un);
          event.set(h_btag_weight_bc_down_un_,   weight_bc_down_un);
          event.set(h_btag_weight_udsg_up_un_,   weight_udsg_up_un);
          event.set(h_btag_weight_udsg_down_un_, weight_udsg_down_un);


          if (sysType_ == "up")        {event.weight *= weight_up;}
          else if (sysType_ == "down")      {event.weight *= weight_down;}
          else if (sysType_ == "up_bc")     {event.weight *= weight_bc_up;}
          else if (sysType_ == "down_bc")   {event.weight *= weight_bc_down;}
          else if (sysType_ == "up_udsg")   {event.weight *= weight_udsg_up;}
          else if (sysType_ == "down_udsg") {event.weight *= weight_udsg_down;}
          else                              {event.weight *= weight;}

          return true;
        }


        // originally taken from https://twiki.cern.ch/twiki/pub/CMS/BTagSFMethods/Method1aExampleCode_CSVM.cc.txt
        std::tuple<float, float, float, float, float> MCBTagScaleFactor::get_weight_btag(const vector<TopJet> &jets, Event & event) {

          float mcTag = 1.;
          float mcNoTag = 1.;
          float dataTag = 1.;
          float dataNoTag = 1.;

          float err1 = 0.;
          float err2 = 0.;
          float err3 = 0.;
          float err4 = 0.;

          float err1_un = 0.;
          float err2_un = 0.;
          float err3_un = 0.;
          float err4_un = 0.;

          //Here we loop over all selected jets
          for (const auto & topjet : jets) { for (const auto & jet : topjet.subjets()) {

            int hadronFlavor = abs(jet.hadronFlavour());
            float abs_eta = fabs(jet.eta());
            float pt = jet.pt();

            if(abs_eta > 2.4) {
              continue;
            }

            TH2* eff_hist;
            if (hadronFlavor == 5) {
              ///here one need to provide the pt/eta dependent efficiency for b-tag for "b jet"
              eff_hist = eff_b_.get();
            }else if( hadronFlavor==4){
              ///here one need to provide the pt/eta dependent efficiency for b-tag for "c jet"
              eff_hist = eff_c_.get();
            }else{
              ///here one need to provide the pt/eta dependent efficiency for b-tag for "light jet"
              eff_hist = eff_udsg_.get();
            }
            const auto eff_pt_axis = eff_hist->GetXaxis();
            float pt_low_edge = eff_pt_axis->GetBinLowEdge(eff_pt_axis->GetFirst());
            float pt_high_edge = eff_pt_axis->GetBinUpEdge(eff_pt_axis->GetLast());
            float pt_for_eff = (pt > pt_low_edge) ? pt : pt_low_edge + 1.;
            pt_for_eff = (pt_for_eff < pt_high_edge) ? pt_for_eff : pt_high_edge - 1.;
            float eff = eff_hist->GetBinContent(eff_hist->FindFixBin(pt_for_eff, abs_eta));

            float SF = 1., SFerr = 0., SFerr_un = 0.;
            std::tie(SF, SFerr) = get_SF_btag(pt, abs_eta, hadronFlavor);
            std::tie(SF, SFerr_un) = get_SF_btag_un(pt, abs_eta, hadronFlavor);

            if (btag_(jet, event)) {
              mcTag *= eff;
              dataTag *= eff*SF;

              if(hadronFlavor==5 || hadronFlavor ==4) { 
              err1 += SFerr/SF; ///correlated for b/c
              err1_un += SFerr_un/SF;
              }
              else{ 
		err3 += SFerr/SF; //correlated for light
		err3_un += SFerr_un/SF;
              }
            }else{
              mcNoTag *= (1- eff);
              dataNoTag *= (1- eff*SF);

              if(hadronFlavor==5 || hadronFlavor ==4 ){
		 err2 += (-eff*SFerr)/(1-eff*SF);
		 err2_un += (-eff*SFerr_un)/(1-eff*SF); /// /correlated for b/c
              }else{
  		 err4 +=  (-eff*SFerr)/(1-eff*SF);  ////correlated for light
                 err4_un +=  (-eff*SFerr_un)/(1-eff*SF);  ////correlated for light
	      }	
            }

          }}

          float wtbtag = (dataNoTag * dataTag ) / ( mcNoTag * mcTag );

          float wtbtagErrBC = fabs(err1+err2) * wtbtag;
          float wtbtagErrUDSG = fabs(err3+err4) * wtbtag;
          float wtbtagErrBC_un = fabs(err1_un+err2_un) * wtbtag;
          float wtbtagErrUDSG_un = fabs(err3_un+err4_un) * wtbtag;


          string errStr = " is NaN in MCBTagScaleFactor::get_weight_btag. Please check that all efficiency-bins are greater than 0.";
          if (isnan(wtbtag)) {
            throw runtime_error("wtbtag" + errStr);
          }
          if (isnan(wtbtagErrBC)) {
            throw runtime_error("wtbtagErrBC" + errStr);
          }
          if (isnan(wtbtagErrUDSG)) {
            throw runtime_error("wtbtagErrUDSG" + errStr);
          }
          if (isnan(wtbtagErrBC_un)) {
            throw runtime_error("wtbtagErrBC" + errStr);
          }
          if (isnan(wtbtagErrUDSG_un)) {
            throw runtime_error("wtbtagErrUDSG" + errStr);
          }
          return std::make_tuple(wtbtag, wtbtagErrBC, wtbtagErrUDSG, wtbtagErrBC_un, wtbtagErrUDSG_un);
        }


        // originally taken from https://twiki.cern.ch/twiki/pub/CMS/BTagSFMethods/Method1aExampleCode_CSVM.cc.txt
        // (only the purpose of the function is the same, interface and implementation changed)
        std::pair<float, float> MCBTagScaleFactor::get_SF_btag(float pt, float abs_eta, int flav) {

          auto btagentry_flav = flav == 5 ? BTagEntry::FLAV_B : (
            flav == 4 ? BTagEntry::FLAV_C :
            BTagEntry::FLAV_UDSG);

            auto sf_bounds = calib_->min_max_pt(btagentry_flav, abs_eta);

            float pt_for_eval = pt;
            bool is_out_of_bounds = false;
            if (pt < sf_bounds.first) {
              pt_for_eval = sf_bounds.first + 1e-5;
              is_out_of_bounds = true;
            } else if (pt > sf_bounds.second) {
              pt_for_eval = sf_bounds.second - 0.1;
              is_out_of_bounds = true;
            }

            float SF_up   = calib_up_->eval(btagentry_flav, abs_eta, pt_for_eval);
            float SF      = calib_->eval(btagentry_flav, abs_eta, pt_for_eval);
            float SF_down = calib_down_->eval(btagentry_flav, abs_eta, pt_for_eval);
            float SFerr_up_ = fabs(SF - SF_up);
            float SFerr_down_ = fabs(SF - SF_down);  // positive value!!
            float SFerr = SFerr_up_ > SFerr_down_ ? SFerr_up_ : SFerr_down_;


            if (is_out_of_bounds) {
              SFerr *= 2;
            }

            if (SF < 1e-10) {
              cout << "WARNING: SF vanishes! Will return SF = 1., SFerr = 0., Values: "
              << "(SF, SFerr, is_out_of_bounds, lowbound, highbound, pt, pt_for_eval, btagentry_flav): "
              << SF << ", " << SFerr << ", " << is_out_of_bounds << ", "
              << sf_bounds.first << ", " << sf_bounds.second << ", "
              << pt << ", " << pt_for_eval << ", " << btagentry_flav << endl;
              SF = 1.;
              SFerr = 0.;
            }
            return std::make_pair(SF, SFerr);
          }


//nuevo
        std::pair<float, float> MCBTagScaleFactor::get_SF_btag_un(float pt, float abs_eta, int flav) {

          auto btagentry_flav = flav == 5 ? BTagEntry::FLAV_B : (
            flav == 4 ? BTagEntry::FLAV_C :
            BTagEntry::FLAV_UDSG);

            auto sf_bounds = calib_->min_max_pt(btagentry_flav, abs_eta);

            float pt_for_eval = pt;
            bool is_out_of_bounds = false;
            if (pt < sf_bounds.first) {
              pt_for_eval = sf_bounds.first + 1e-5;
              is_out_of_bounds = true;
            } else if (pt > sf_bounds.second) {
              pt_for_eval = sf_bounds.second - 0.1;
              is_out_of_bounds = true;
            }

            float SF      = calib_->eval(btagentry_flav, abs_eta, pt_for_eval);
            float SF_up_un   = calib_up_un_->eval(btagentry_flav, abs_eta, pt_for_eval);
            float SF_down_un = calib_down_un_->eval(btagentry_flav, abs_eta, pt_for_eval);
            float SFerr_up_un_ = fabs(SF - SF_up_un);
            float SFerr_down_un_ = fabs(SF - SF_down_un);  // positive value!!
            float SFerr_un = SFerr_up_un_ > SFerr_down_un_ ? SFerr_up_un_ : SFerr_down_un_;


            if (is_out_of_bounds) {
              SFerr_un *= 2;
            }

            if (SF < 1e-10) {
              cout << "WARNING: SF vanishes! Will return SF = 1., SFerr = 0., Values: "
              << "(SF, SFerr, is_out_of_bounds, lowbound, highbound, pt, pt_for_eval, btagentry_flav): "
              << SF << ", " << SFerr_un << ", " << is_out_of_bounds << ", "
              << sf_bounds.first << ", " << sf_bounds.second << ", "
              << pt << ", " << pt_for_eval << ", " << btagentry_flav << endl;
              SF = 1.;
              SFerr_un = 0.;
            }
            return std::make_pair(SF, SFerr_un);
          }


          // Originally copied from https://github.com/reimersa/UHH2/blob/RunII_94X_v1/common/src/MCWeight.cxx#L851
          // Old class name: 'MCCSVv2ShapeSystematic'
          // This new version also works for DeepJet and DeepCSV!
          MCBTagDiscriminantReweighting::MCBTagDiscriminantReweighting(uhh2::Context & ctx,
            BTag::algo algorithm,
            const std::string & jets_handle_name,
            const std::string & sysType,
            const std::string & measType,
            const std::string & weights_name_postfix,
            const std::string & xml_calib_name):
            algorithm_(algorithm),
            h_jets_(ctx.get_handle<std::vector<Jet>>(jets_handle_name)),
            sysType_(sysType),
            h_weight_btagdisc_central (ctx.declare_event_output<float>("weight_btagdisc_central"+weights_name_postfix)),
            h_weight_btagdisc_jesup (ctx.declare_event_output<float>("weight_btagdisc_jesup"+weights_name_postfix)),
            h_weight_btagdisc_jesdown (ctx.declare_event_output<float>("weight_btagdisc_jesdown"+weights_name_postfix)),
            h_weight_btagdisc_lfup (ctx.declare_event_output<float>("weight_btagdisc_lfup"+weights_name_postfix)),
            h_weight_btagdisc_lfdown (ctx.declare_event_output<float>("weight_btagdisc_lfdown"+weights_name_postfix)),
            h_weight_btagdisc_hfup (ctx.declare_event_output<float>("weight_btagdisc_hfup"+weights_name_postfix)),
            h_weight_btagdisc_hfdown (ctx.declare_event_output<float>("weight_btagdisc_hfdown"+weights_name_postfix)),
            h_weight_btagdisc_hfstats1up (ctx.declare_event_output<float>("weight_btagdisc_hfstats1up"+weights_name_postfix)),
            h_weight_btagdisc_hfstats1down (ctx.declare_event_output<float>("weight_btagdisc_hfstats1down"+weights_name_postfix)),
            h_weight_btagdisc_hfstats2up (ctx.declare_event_output<float>("weight_btagdisc_hfstats2up"+weights_name_postfix)),
            h_weight_btagdisc_hfstats2down (ctx.declare_event_output<float>("weight_btagdisc_hfstats2down"+weights_name_postfix)),
            h_weight_btagdisc_lfstats1up (ctx.declare_event_output<float>("weight_btagdisc_lfstats1up"+weights_name_postfix)),
            h_weight_btagdisc_lfstats1down (ctx.declare_event_output<float>("weight_btagdisc_lfstats1down"+weights_name_postfix)),
            h_weight_btagdisc_lfstats2up (ctx.declare_event_output<float>("weight_btagdisc_lfstats2up"+weights_name_postfix)),
            h_weight_btagdisc_lfstats2down (ctx.declare_event_output<float>("weight_btagdisc_lfstats2down"+weights_name_postfix)),
            h_weight_btagdisc_cferr1up (ctx.declare_event_output<float>("weight_btagdisc_cferr1up"+weights_name_postfix)),
            h_weight_btagdisc_cferr1down (ctx.declare_event_output<float>("weight_btagdisc_cferr1down"+weights_name_postfix)),
            h_weight_btagdisc_cferr2up (ctx.declare_event_output<float>("weight_btagdisc_cferr2up"+weights_name_postfix)),
            h_weight_btagdisc_cferr2down (ctx.declare_event_output<float>("weight_btagdisc_cferr2down"+weights_name_postfix))
            {
              auto dataset_type = ctx.get("dataset_type");
              bool is_mc = dataset_type == "MC";
              if (!is_mc) {
                cout << "Warning: MCBTagDiscriminantReweighting will not have an effect on "
                <<" this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
                return;
              }


             BTagCalibration calibration("tagger", ctx.get(xml_calib_name)); // CHECK: the first std::string argument here should not be relevant
              reader.reset(new BTagCalibrationReader(BTagEntry::OP_RESHAPING,"central",
              {"up_jes","down_jes",
              "up_lf","down_lf",
              "up_hf","down_hf",
              "up_hfstats1","down_hfstats1",
              "up_hfstats2","down_hfstats2",
              "up_lfstats1","down_lfstats1",
              "up_lfstats2","down_lfstats2",
              "up_cferr1","down_cferr1",
              "up_cferr2","down_cferr2"}));
              reader->load(calibration,BTagEntry::FLAV_B,measType);
              reader->load(calibration,BTagEntry::FLAV_C,measType);
              reader->load(calibration,BTagEntry::FLAV_UDSG,measType);

            }

            bool MCBTagDiscriminantReweighting::process(Event & event) {

              if (event.isRealData) {
                event.set(h_weight_btagdisc_central,1.);
                event.set(h_weight_btagdisc_jesup,1.);
                event.set(h_weight_btagdisc_jesdown,1.);
                event.set(h_weight_btagdisc_lfup,1.);
                event.set(h_weight_btagdisc_lfdown,1.);
                event.set(h_weight_btagdisc_hfup,1.);
                event.set(h_weight_btagdisc_hfdown,1.);
                event.set(h_weight_btagdisc_hfstats1up,1.);
                event.set(h_weight_btagdisc_hfstats1down,1.);
                event.set(h_weight_btagdisc_hfstats2up,1.);
                event.set(h_weight_btagdisc_hfstats2down,1.);
                event.set(h_weight_btagdisc_lfstats1up,1.);
                event.set(h_weight_btagdisc_lfstats1down,1.);
                event.set(h_weight_btagdisc_lfstats2up,1.);
                event.set(h_weight_btagdisc_lfstats2down,1.);
                event.set(h_weight_btagdisc_cferr1up,1.);
                event.set(h_weight_btagdisc_cferr1down,1.);
                event.set(h_weight_btagdisc_cferr2up,1.);
                event.set(h_weight_btagdisc_cferr2down,1.);
                return true;
              }


              float weight_central = 1.0;
              float weight_jesup = 1.0;
              float weight_jesdown = 1.0;
              float weight_lfup = 1.0;
              float weight_lfdown = 1.0;
              float weight_hfup = 1.0;
              float weight_hfdown = 1.0;
              float weight_hfstats1up = 1.0;
              float weight_hfstats1down = 1.0;
              float weight_hfstats2up = 1.0;
              float weight_hfstats2down = 1.0;
              float weight_lfstats1up = 1.0;
              float weight_lfstats1down = 1.0;
              float weight_lfstats2up = 1.0;
              float weight_lfstats2down = 1.0;
              float weight_cferr1up = 1.0;
              float weight_cferr1down = 1.0;
              float weight_cferr2up = 1.0;
              float weight_cferr2down = 1.0;

              const auto & jets = event.get(h_jets_);
              for (size_t ijet=0; ijet < jets.size(); ijet++) {
                Jet jet = jets.at(ijet);
                float jet_pt = jet.pt();
                float jet_eta = jet.eta();

                float jet_btagdisc;
                if      (algorithm_ == BTag::CSVV2)   jet_btagdisc = jet.btag_combinedSecondaryVertex();
                else if (algorithm_ == BTag::DEEPCSV) jet_btagdisc = jet.btag_DeepCSV();
                else if (algorithm_ == BTag::DEEPJET) jet_btagdisc = jet.btag_DeepJet();
                else throw runtime_error("MCBTagDiscriminantReweighting::process: Given b-tagging algorithm is (right now) not suited to be used jointly with this routine. Please check if it is compatible and then add your chosen algorithm as option to this analysis module. Adjust the routine if necessary.");

                if (jet_btagdisc < 0.0) jet_btagdisc = -0.05;
                if (jet_btagdisc > 1.0) jet_btagdisc = 1.0;

                BTagEntry::JetFlavor jet_flavor = BTagEntry::FLAV_UDSG;
                if (abs(jet.hadronFlavour()) == 5) jet_flavor = BTagEntry::FLAV_B;
                else if (abs(jet.hadronFlavour()) == 4) jet_flavor = BTagEntry::FLAV_C;

                if( jet_pt > 20.0 && fabs(jet_eta) < 2.4) {
                  weight_central *= reader->eval_auto_bounds("central",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                  if (jet_flavor == BTagEntry::FLAV_B) {
                    weight_jesup *= reader->eval_auto_bounds("up_jes",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_jesdown *= reader->eval_auto_bounds("down_jes",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_lfup *= reader->eval_auto_bounds("up_lf",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_lfdown *= reader->eval_auto_bounds("down_lf",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_hfstats1up *= reader->eval_auto_bounds("up_hfstats1",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_hfstats1down *= reader->eval_auto_bounds("down_hfstats1",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_hfstats2up *= reader->eval_auto_bounds("up_hfstats2",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_hfstats2down *= reader->eval_auto_bounds("down_hfstats2",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                  }
                  if (jet_flavor == BTagEntry::FLAV_C) {
                    weight_cferr1up *= reader->eval_auto_bounds("up_cferr1",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_cferr1down *= reader->eval_auto_bounds("down_cferr1",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_cferr2up *= reader->eval_auto_bounds("up_cferr2",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_cferr2down *= reader->eval_auto_bounds("down_cferr2",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                  }
                  if (jet_flavor == BTagEntry::FLAV_UDSG) {
                    weight_jesup *= reader->eval_auto_bounds("up_jes",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_jesdown *= reader->eval_auto_bounds("down_jes",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_hfup *= reader->eval_auto_bounds("up_hf",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_hfdown *= reader->eval_auto_bounds("down_hf",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_lfstats1up *= reader->eval_auto_bounds("up_lfstats1",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_lfstats1down *= reader->eval_auto_bounds("down_lfstats1",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_lfstats2up *= reader->eval_auto_bounds("up_lfstats2",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                    weight_lfstats2down *= reader->eval_auto_bounds("down_lfstats2",jet_flavor, jet_eta, jet_pt, jet_btagdisc);
                  }
                }
              }

              event.set(h_weight_btagdisc_central, weight_central);
              event.set(h_weight_btagdisc_jesup, weight_jesup);
              event.set(h_weight_btagdisc_jesdown, weight_jesdown);
              event.set(h_weight_btagdisc_lfup, weight_lfup);
              event.set(h_weight_btagdisc_lfdown, weight_lfdown);
              event.set(h_weight_btagdisc_hfup, weight_hfup);
              event.set(h_weight_btagdisc_hfdown, weight_hfdown);
              event.set(h_weight_btagdisc_hfstats1up, weight_hfstats1up);
              event.set(h_weight_btagdisc_hfstats1down, weight_hfstats1down);
              event.set(h_weight_btagdisc_hfstats2up, weight_hfstats2up);
              event.set(h_weight_btagdisc_hfstats2down, weight_hfstats2down);
              event.set(h_weight_btagdisc_lfstats1up, weight_lfstats1up);
              event.set(h_weight_btagdisc_lfstats1down, weight_lfstats1down);
              event.set(h_weight_btagdisc_lfstats2up, weight_lfstats2up);
              event.set(h_weight_btagdisc_lfstats2down, weight_lfstats2down);
              event.set(h_weight_btagdisc_cferr1up, weight_cferr1up);
              event.set(h_weight_btagdisc_cferr1down, weight_cferr1down);
              event.set(h_weight_btagdisc_cferr2up, weight_cferr2up);
              event.set(h_weight_btagdisc_cferr2down, weight_cferr2down);

              if (sysType_ == "jesup") {event.weight *= weight_jesup;}
              else if (sysType_ == "jesdown") {event.weight *= weight_jesdown;}
              else if (sysType_ == "lfup") {event.weight *= weight_lfup;}
              else if (sysType_ == "lfdown") {event.weight *= weight_lfdown;}
              else if (sysType_ == "hfup") {event.weight *= weight_hfup;}
              else if (sysType_ == "hfdown") {event.weight *= weight_hfdown;}
              else if (sysType_ == "hfstats1up") {event.weight *= weight_hfstats1up;}
              else if (sysType_ == "hfstats1down") {event.weight *= weight_hfstats1down;}
              else if (sysType_ == "hfstats2up") {event.weight *= weight_hfstats2up;}
              else if (sysType_ == "hfstats2down") {event.weight *= weight_hfstats2down;}
              else if (sysType_ == "lfstats1up") {event.weight *= weight_lfstats1up;}
              else if (sysType_ == "lfstats1down") {event.weight *= weight_lfstats1down;}
              else if (sysType_ == "lfstats2up") {event.weight *= weight_lfstats2up;}
              else if (sysType_ == "lfstats2down") {event.weight *= weight_lfstats2down;}
              else if (sysType_ == "cferr1up") {event.weight *= weight_cferr1up;}
              else if (sysType_ == "cferr1down") {event.weight *= weight_cferr1down;}
              else if (sysType_ == "cferr2up") {event.weight *= weight_cferr2up;}
              else if (sysType_ == "cferr2down") {event.weight *= weight_cferr2down;}
//              else {event.weight *= weight_central;}
              
              return true;
            }


            TauEffVariation::TauEffVariation(Context & ctx){

              auto dataset_type = ctx.get("dataset_type");
              bool is_mc = dataset_type == "MC";
              if(!is_mc){
                cout << "Warning: TauIdVariation will not have an effect on this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
                return;
              }
              auto s_TauEff = ctx.get("TauIdVariation");

              if(s_TauEff == "up") {i_TauEff = 1;}
              else if(s_TauEff == "down"){i_TauEff = 2;}

            }
            bool TauEffVariation::process(Event & event){
              if (event.isRealData) return true;

              std::vector<Tau> real_taus;
              for(unsigned int j=0; j<event.taus->size(); ++j)
              {
                bool real = false;
                Tau tau = event.taus->at(j);
                try{
                  for(unsigned int i=0; i<event.genparticles->size(); ++i)
                  {
                    GenParticle genp = event.genparticles->at(i);
                    double dr = deltaR(genp,tau);
                    if (dr < 0.4 && abs(genp.pdgId())==15) real = true;
                  }
                }
                catch(const std::runtime_error& error){
                  std::cout<<"Problem with genparticles in MCWeight.cxx"<<std::endl;
                  std::cout<<error.what();
                }
                if(real) real_taus.push_back(tau);
              }
              for(unsigned int i=0; i<real_taus.size(); ++i)
              {
                Tau realtau = real_taus.at(i);
                if (i_TauEff==0)
                {
                  event.weight *= SF_TauId;
                }
                if (i_TauEff==1)
                {
                  event.weight *= (SF_TauId+0.10)+0.2*realtau.pt()/1000;
                }
                if (i_TauEff==2)
                {
                  event.weight *= (SF_TauId-0.10)-0.2*realtau.pt()/1000;
                }
              }
              return true;
            }

            TauChargeVariation::TauChargeVariation(Context & ctx){
              auto dataset_type = ctx.get("dataset_type");
              bool is_mc = dataset_type == "MC";
              if(!is_mc){
                cout << "Warning: TauChargeVariation will not have an effect on this non-MC sample (dataset_type = '" + dataset_type + "')" << endl;
                return;
              }
              auto s_TauCharge = ctx.get("TauChargeVariation");

              if(s_TauCharge == "up") {i_TauCharge = 1;}
              else if(s_TauCharge == "down"){i_TauCharge = 2;}

            }
            bool TauChargeVariation::process(Event & event){
              if (event.isRealData) return true;

              for(unsigned int j=0; j<event.taus->size(); ++j)
              {
                Tau tau = event.taus->at(j);
                try{
                  for(unsigned int i=0; i<event.genparticles->size(); ++i)
                  {
                    GenParticle genp = event.genparticles->at(i);
                    double dr = deltaR(genp,tau);
                    if (dr < 0.4 && abs(genp.pdgId())==15){
                      if(tau.charge()!=genp.charge()){
                        if(i_TauCharge==0) {return true;}
                        if(i_TauCharge==1){
                          event.weight *= 1.02;
                        }
                        if(i_TauCharge==2){
                          event.weight *= 0.98;
                        }
                      }
                    }
                  }
                }
                catch(const std::runtime_error& error){
                  std::cout<<"Problem with genInfo in MCWeight.cxx"<<std::endl;
                  std::cout<<error.what();
                }
              }
              return true;
            }
