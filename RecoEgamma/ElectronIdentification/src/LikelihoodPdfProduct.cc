#include "RecoEgamma/ElectronIdentification/interface/LikelihoodPdfProduct.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <iostream>



LikelihoodPdfProduct::LikelihoodPdfProduct(const char* name, 
					   int ecalsubdet, int ptbin) 
{
  _name=std::string(name);
  _ecalsubdet = ecalsubdet;
  _ptbin = ptbin;
}



LikelihoodPdfProduct::~LikelihoodPdfProduct() 
{
  // do the delete's 
  std::vector<LikelihoodSpecies*>::iterator specItr;
  for(specItr=_specList.begin(); specItr!=_specList.end(); specItr++) {
    delete *specItr;
  }
}



void 
LikelihoodPdfProduct::initFromDB(const ElectronLikelihoodCalibration *calibration) 
{
  _calibration=calibration;
}



void 
LikelihoodPdfProduct::addSpecies(const char* name, float priorWeight) 
{
  LikelihoodSpecies* species = new LikelihoodSpecies(name,priorWeight);
  _specList.push_back(species);
}



void 
LikelihoodPdfProduct::addPdf(const char* specname, 
			     const char* name, 
			     bool splitPdf) 
{
  std::vector<LikelihoodSpecies*>::const_iterator specItr;
  for(specItr=_specList.begin();specItr!=_specList.end();specItr++) {
    LikelihoodSpecies* species = *specItr;
    if(strcmp(species->getName(),specname)==0) {
      LikelihoodPdf *pdf = new LikelihoodPdf(name,species->getName(),_ecalsubdet,_ptbin);
      pdf->split(species->getSplitFractions(),splitPdf);
      pdf->initFromDB(_calibration);
      species->addPdf(pdf);
    }
  }
}



void 
LikelihoodPdfProduct::setSplitFrac(const char* specname, 
				   const char* catName, float frac) {
  std::vector<LikelihoodSpecies*>::const_iterator specItr;
  for(specItr=_specList.begin();specItr!=_specList.end();specItr++) {
    LikelihoodSpecies* species = *specItr;
    if(strcmp(species->getName(),specname)==0) {
      species->setSplitFraction( make_pair(std::string(catName), frac) );
      break;
    }
  }
}



float 
LikelihoodPdfProduct::getRatio(const char* specname, 
			       std::vector<float> measurements, 
			       std::string gsfClass) 
{
  float sigProb=0, bkgProb=0;
  std::vector<LikelihoodSpecies*>::const_iterator specItr;
  for(specItr=_specList.begin();specItr!=_specList.end();specItr++) {
    LikelihoodSpecies* species = *specItr;
    std::map<std::string,float> splitFractions = species->getSplitFractions();
    std::map<std::string,float>::iterator iter = splitFractions.find(gsfClass);
    //! if the pdf is not splitted, assign the split fraction = 1
    float splitFr= (splitFractions.size()==0) ? 1. : iter->second;
    if(strcmp(species->getName(),specname)==0) {
      sigProb=splitFr*getSpeciesProb(specname,measurements,gsfClass);
    }
    else {
      bkgProb+=splitFr*getSpeciesProb(species->getName(),measurements,gsfClass);
    } 
  }
  if(sigProb+bkgProb>0)
    return sigProb/(sigProb+bkgProb);
  else
    return -1.;
}



float 
LikelihoodPdfProduct::getSpeciesProb(const char* specName, 
				     std::vector<float> measurements, 
				     std::string gsfClass) 
{
  float bareProb=1.;
  float priorWeight=1.;
  std::vector<LikelihoodSpecies*>::const_iterator specItr;
  for(specItr=_specList.begin();specItr!=_specList.end();specItr++) {
    LikelihoodSpecies* species = *specItr;
    if(strcmp(species->getName(),specName)==0) {
      for(unsigned int ipdf=0; ipdf< species->getListOfPdfs().size(); ipdf++) {
        bareProb*=species->getListOfPdfs().at(ipdf)->getVal(measurements.at(ipdf),gsfClass);
      }
      priorWeight=species->getPrior();
      break;
    }
  }
  edm::LogInfo("LikelihoodPdfProduct") << "Species: " << specName
				       << " bare probability = " << bareProb
				       << " with a priori probability = " << priorWeight;
  return priorWeight*bareProb;
}
