/*
**	Filename : Plot_gamma.cpp
**	2024-01-25
**	username : rsehgal
*/
#include <TApplication.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TTree.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
int main(int argc, char *argv[]) {

  // TCanvas *can = new TCanvas;
  TApplication *fApp = new TApplication("test", NULL, NULL);
  // std::string particle = argv[1];
  std::vector<float> xvec; // = {200,400,600,800,1000,1500,2000,2500,3000,4000,5000,6000,7000,8000,9000,10000};
  std::vector<float> yvec;

  TMultiGraph *multiGraph = new TMultiGraph();
  TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);

  std::cout << "============== Energy KeV ====================" << std::endl;
  for (unsigned int i = 200; i < 1900; i += 200) {
    xvec.push_back(i);
    std::cout << i << " , ";
  }
  std::cout << std::endl;

  std::vector<std::string> incidentParticles = {"neutron", "gamma"};
  // std::vector<std::string> vecOfParticles = {"e+", "e-", "gamma", "neutron"}; //, "nu_e", "anti_nue_e"};
  std::vector<std::string> vecOfParticles = {"e-", "gamma"};

  std::map<std::string, std::vector<float>> particleMap;

  for (unsigned int j = 0; j < vecOfParticles.size(); j++) {
    particleMap[vecOfParticles[j]] = std::vector<float>{};
  }

  std::string incidentParticle = argv[1];
  // for (unsigned int i = 1200; i < 2100; i += 200) {
  for (auto i : xvec) {
    // std::string filename = incidentPartilces[incpart] + "_" + std::to_string(i) + "_" + std::to_string(i) + ".root";
    std::string filename = incidentParticle + "_" + std::to_string((int)i) + "_" + std::to_string((int)i) + ".root";
    TFile *fp = new TFile(filename.c_str(), "r");

    for (unsigned int j = 0; j < vecOfParticles.size(); j++) {
      TTree *tree = (TTree *)fp->Get((vecOfParticles[j] + "_SensitiveHollowSpace").c_str());
      if (tree) {
        // particleMap[vecOfParticles[j]].push_back(std::log10(tree->GetEntries()));
        particleMap[vecOfParticles[j]].push_back(tree->GetEntries());
      } else {
        // particleMap[vecOfParticles[j]].push_back(std::log10(1));
        particleMap[vecOfParticles[j]].push_back(0);
      }
    }
  }

  for (auto it = particleMap.begin(); it != particleMap.end(); ++it) {
    // std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "Key : " << it->first << " : Size : " << (it->second).size() << std::endl;
    for (unsigned int i = 0; i < (it->second).size(); i++) {
      std::cout << (it->second)[i] << " , ";
    }
    std::cout << std::endl;
  }

  unsigned short counter = 0;
  for (auto it = particleMap.begin(); it != particleMap.end(); ++it) {
    counter++;
    TGraph *gr = new TGraph(xvec.size(), &xvec[0], &(it->second)[0]);
    gr->SetTitle((it->first).c_str());
    gr->SetMarkerStyle(8);
    gr->SetLineColor(counter);
    gr->SetMarkerColor(counter);
    multiGraph->Add(gr);
    legend->AddEntry(gr);
  }

  multiGraph->Draw("apl");
  legend->Draw();

  TLatex latex;
  latex.DrawLatex(800, 3100, ("Incident Particles : 10^7  " + incidentParticle).c_str());
  latex.DrawLatex(800, 3000, "Particles reaching the detector volume");

  fApp->Run();

  return 0;
}
