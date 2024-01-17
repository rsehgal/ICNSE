/*
**	Filename : Analysis.cpp
**	2024-01-09
**	username : rsehgal
*/
#include "Analysis.h"
#include <TFile.h>
#include <TH1F.h>
#include <iostream>

Analysis *Analysis::s_instance = 0;

Analysis *Analysis::Create(std::string filename) {
  if (!s_instance)
    s_instance = new Analysis(filename);
  return s_instance;
}

Analysis *Analysis::Instance() {
  if (!s_instance)
    std::cout << "Analysis object does not exist in memory, Please create it first..." << std::endl;
  else
    return s_instance;
}

Analysis::Analysis(std::string filename) {
  fp = new TFile(filename.c_str(), "RECREATE");
  fHistGamma = new TH1F("GammaHistogram", "GammaHistogram", 1000, 0, 8000);
}

void Analysis::FillGammaHistogram(double energy) {
  // std::cout << "Energy : " << energy << std::endl;
  fHistGamma->Fill(energy);
}

void Analysis::Close() {
  fp->cd();
  fHistGamma->Write();
  fp->Close();
}