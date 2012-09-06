

#ifndef HistoMessenger_h
#define HistoMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Histo;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoMessenger: public G4UImessenger
{
  public:

   HistoMessenger(Histo* );
  ~HistoMessenger();

   void SetNewValue(G4UIcommand* ,G4String );

  private:

   Histo*                  histo;
   
   G4UIdirectory*          histoDir;   
   G4UIcmdWithAString*     factoryCmd;
   G4UIcmdWithAString*     fileCmd;
   G4UIcommand*            histoCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
