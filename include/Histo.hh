


#ifndef Histo_h
#define Histo_h 1


#include "globals.hh"
#include <vector>
#include "G4DynamicParticle.hh"
#include "G4VPhysicalVolume.hh"
#include "G4DataVector.hh"
#include "G4Track.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class HistoMessenger;

namespace AIDA {
  class ITree;
  class ITuple;
  class IHistogram1D;
  class IAnalysisFactory;
}

class Histo
{

public:
  Histo();

  ~Histo();

  void book();
  // Book predefined histogramms 

  void save();
  // Save histogramms to file

  void add1D(const G4String&, const G4String&, G4int nb=100, G4double x1=0., 
                                               G4double x2=1., G4double u=1.);
  // In this method histogramms are predefined

  void setHisto1D(G4int, G4int, G4double, G4double, G4double);
  // It change bins and boundaries

  void fill(G4int, G4double, G4double);
  // Histogramms are filled

  void scale(G4int, G4double);

  void addTuple(const G4String&, const G4String&, const G4String&);
  // In this method nTuple is booked

  void fillTuple(const G4String&, G4double);
  // Fill nTuple parameter

  void addRow();
  // Save tuple event 

  void setFileName(const G4String&);

  void setFileType(const G4String&);

private:
 
  G4String histName;
  G4String histType;
  G4String tupleName;
  G4String tupleId;
  G4String tupleList;
  G4int    nHisto;
  G4int    verbose;
  G4int    defaultAct;

  std::vector<AIDA::IHistogram1D*> histo;
  AIDA::IAnalysisFactory* af;  
  AIDA::ITuple*   ntup;
  AIDA::ITree*    tree;
  HistoMessenger* messenger;
  std::vector<G4int>     active;
  std::vector<G4int>     bins;
  std::vector<G4double>  xmin;
  std::vector<G4double>  xmax;
  std::vector<G4double>  unit;
  std::vector<G4String>  ids;
  std::vector<G4String>  titles;
};

#endif
