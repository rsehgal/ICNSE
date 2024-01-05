/*
**	Filename : Helpers.cpp
**	2024-01-05
**	username : rsehgal
*/
#include "Helpers.h"
#include <iostream>
#include "SD.h"
void PrintSummary(unsigned int numOfEvents) {
  std::cout << "================== SUMMARY ===========================================" << std::endl;
  std::cout << "Total Number of Event : " << numOfEvents << std::endl;
  std::cout << "No of Particles reaches Sensitive Detector Region : " << SD::numOfParticlesReached << std::endl;
  std::cout << "===================Particle breakup are as follow ====================" << std::endl;
  for (const auto &pair : SD::fParticleCounter) {
    std::cout << "Particle : " << pair.first << " , Count : " << pair.second << std::endl;
  }

  std::cout << "======================================================================" << std::endl;
}
