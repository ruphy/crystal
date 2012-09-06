#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "HistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::PhysicsListMessenger(PhysicsList* pPhys)
:pPhysicsList(pPhys)
{   
  eCmd = new G4UIcmdWithADoubleAndUnit("/testem/phys/setMaxE",this);  
  eCmd->SetGuidance("Set max energy deposit");
  eCmd->SetParameterName("Emax",false);
  eCmd->SetUnitCategory("Energy");
  eCmd->SetRange("Emax>0.0");
  eCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ebCmd = new G4UIcmdWithAnInteger("/testem/phys/setNbinsE",this);  
  ebCmd->SetGuidance("Set number of bins in energy.");
  ebCmd->SetParameterName("Ebins",false);
  ebCmd->SetRange("Ebins>0");
  ebCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  cbCmd = new G4UIcmdWithAnInteger("/testem/phys/setNbinsCl",this);  
  cbCmd->SetGuidance("Set max number of clusters.");
  cbCmd->SetParameterName("Cbins",false);
  cbCmd->SetRange("Cbins>0");
  cbCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  pListCmd = new G4UIcmdWithAString("/testem/phys/addPhysics",this);  
  pListCmd->SetGuidance("Add modula physics list.");
  pListCmd->SetParameterName("PList",false);
  pListCmd->AvailableForStates(G4State_PreInit);  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete eCmd;
  delete ebCmd;
  delete cbCmd;
  delete pListCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{   
  /*HistoManager* man = HistoManager::GetPointer();
  if( command == eCmd )
   { man->SetMaxEnergy(eCmd->GetNewDoubleValue(newValue));}
     
  if( command == ebCmd )
   { man->SetNumberBins(ebCmd->GetNewIntValue(newValue));}
     
  if( command == cbCmd )
   { man->SetNumberBinsCluster(cbCmd->GetNewIntValue(newValue));}

  if( command == pListCmd )
   { pPhysicsList->AddPhysicsList(newValue);}
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
