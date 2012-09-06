// Martin Goettlich @ DESY
//

#include "G4Timer.hh"

#include "RunAction.hh"

#include "G4Run.hh"

#include "CreateTree.hh"


RunAction::RunAction()
{
  timer = new G4Timer;
}

RunAction::~RunAction()
{
  delete timer;
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  timer->Start();

  CreateTree::Instance()-> Run = aRun->GetRunID();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{   
  timer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent() 
         << " " << *timer << G4endl;
}


