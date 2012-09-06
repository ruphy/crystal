
#ifndef HistoManager_h
#define HistoManager_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "globals.hh"
#include "G4DataVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class Histo;
class G4Step;
class G4ElectronIonPair;

class HistoManager
{

public:
  // With description

  static HistoManager* GetPointer();

private:

  HistoManager();

public: // Without description

  ~HistoManager();

  void bookHisto();

  void BeginOfRun();
  void EndOfRun();

  void BeginOfEvent();
  void EndOfEvent();

  void AddEnergy(G4double edep, G4Step*);

  inline void SetMaxEnergy(G4double value);

  inline void SetNumberBins(G4int value);

  inline void SetNumberBinsCluster(G4int value);

  inline void SetVerbose(G4int value);

  inline G4int GetVerbose() const;

private:

  // MEMBERS
  static HistoManager* fManager;

  G4int nHisto;
  G4int verbose;

  G4double maxEnergy;
  G4double nStepGas;
  G4double nCluster;
  G4double nTotStepGas;
  G4double nTotCluster;
  G4double nEvt;

  G4int nBinsE; 
  G4int nBinsCluster;

  G4double totEdep;
  G4double overflow;
  G4DataVector Egas;

  Histo*    histo;
  G4ElectronIonPair* elIonPair;
};

inline void HistoManager::SetMaxEnergy(G4double value)
{
  maxEnergy = value;
}

inline void HistoManager::SetNumberBins(G4int value)
{
  nBinsE = value;
}

inline void HistoManager::SetNumberBinsCluster(G4int value)
{
  nBinsCluster = value;
}

inline void HistoManager::SetVerbose(G4int value)
{
  verbose = value;
}

inline G4int HistoManager::GetVerbose() const
{
  return verbose;
}

#endif
